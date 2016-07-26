#pragma once

/**
* @author Anima Seteine
* @purpose This writer, unlike xml_writer, was not designed to be used by the parse tree.
*          Instead, it is a utility class that help construct HTML files using xml_writer.
*/


#include "xml_writer.h"

namespace fabula
{
	class HtmlWriter : public parsing::XmlWriter
	{
	public:

		HtmlWriter(std::ostream& stream)
			: XmlWriter(stream, false) {}

		void doctype() { this->writeBytes("<!DOCTYPE html>"); }

		void header(const std::string& title,
			        const std::initializer_list<const std::string>& cssDir)
		{
			push("header");
			push("title");
			writeBytes(title);
			pop();
			for (const std::string& dir : cssDir)
				singleTag("link", { {"rel", "stylesheet"}, {"type","text/css"}, {"href", dir.c_str()} });
			pop();
		}

		void br()
		{
			singleTag("br");
		}
	};
}