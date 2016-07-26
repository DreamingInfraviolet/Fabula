#include "xml_writer.h"

namespace fabula
{
	namespace parsing
	{
		XmlWriter::XmlWriter(std::ostream& stream, bool surroundWithQuotes)
			: Writer(stream), mSurroundWithQuotes(surroundWithQuotes) {}

		void XmlWriter::indent(int level)
		{
			for (int i = 0; i < level; ++i)
				stream << "    ";
		}

		void XmlWriter::push(const std::string& name,
			const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes)
		{
			stack.push_back(name);
			++indentationLevel;
			writeOpenTagText(name, attributes, false);
		}

		void XmlWriter::singleTag(const std::string& name,
				const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes)
		{
			writeOpenTagText(name, attributes, true);
		}

		void XmlWriter::writeOpenTagText(const std::string& name,
	              const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes,
			      bool single)
		{
			indent(indentationLevel);
			stream << "<" << name;
			for (auto& attr : attributes)
				stream << " " << attr.first << "=\"" << attr.second << "\"";
			stream << (single ? "/>\n" : ">\n");
		}

		void XmlWriter::pop()
		{
			std::string name = stack.back();
			stack.pop_back();
			indent(--indentationLevel);
			stream << "</" << name << ">\n";
		}

		void XmlWriter::writeBytes(const std::string& bytes)
		{
			indent(indentationLevel);
			if(mSurroundWithQuotes)
					stream << "\"" << bytes << "\"" << "\n";
			else
				stream << bytes << "\n";
		}
	}
}