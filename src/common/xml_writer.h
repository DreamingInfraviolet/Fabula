#pragma once

/**
* @author Anima Seteine
* @purpose Overides the writer interface to allow for writing to readable xml.
*/

#include<sstream>
#include<string>
#include <vector>
#include "writer.h"

namespace fabula
{
	namespace parsing
	{
		class XmlWriter : public Writer
		{
			std::vector<std::string> stack;
			int indentationLevel = 0;

			void indent(int level);

			void writeOpenTagText(const std::string& name,
				const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes,
				bool single);

			bool mSurroundWithQuotes;
		public:

			XmlWriter(std::ostream& stream, bool surroundWithQuotes=true);

			//Overriden
			virtual void push(const std::string& name,
				const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes = {});
			virtual void writeBytes(const std::string& bytes);
			virtual void pop();

			/** Writes a single tag. */
			void singleTag(const std::string& name,
				const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes = {});
		};
	}
}