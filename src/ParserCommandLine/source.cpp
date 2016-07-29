#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "fparser.h"
#include "parse_exception.h"
#include "xml_writer.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        fabula::parsing::Parser* parser = fabula::parsing::Parser::create(std::cin, "");
        parser->parse();
        fabula::parsing::XmlWriter writer(std::cout);
        parser->write(writer);
        fabula::parsing::Parser::destroy(parser);
    }
    catch(const fabula::parsing::ParseException& e)
    {
        std::cout << "Compilation error:\n" << e.what() << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Unknown error:\n" << e.what() << "\n";
    }
}
