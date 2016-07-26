#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "fparser.h"
#include "xml_writer.h"

using namespace std;

int main(int argc, char** argv)
{
	fabula::parsing::Parser* parser = fabula::parsing::Parser::create(std::cin, "");
	parser->parse();
	fabula::parsing::XmlWriter writer(std::cout);
	parser->write(writer);
	fabula::parsing::Parser::destroy(parser);
}