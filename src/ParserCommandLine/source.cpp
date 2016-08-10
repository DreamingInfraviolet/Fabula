#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "fparser.h"
#include "parse_exception.h"
#include "xml_writer.h"
#include "docopt.h"
#include "file_io.h"

using namespace std;

const char* usage =
R"(Usage:
    fabula [options]
Options:
        -i=<input_file> --input-file=<input_file>      The input file to read from. If not specified, will read from console [default: ]
        -o=<output_file> --output-file=<output_file>   The output file to write to. If not specified, will print to console [default: ]
        -f=<output_format> --format=<output_format>    The output format to use [default: xml]

Welcome to the Glorious Fabula Compiler! ^_^
This is a very simple tool that can read fabula code and generate an intermediate representation of the code.
It is not designed for generating stories, but only for allowing interoperability with other tools that may
not wish to use a C++ interface.
)";

std::string readFromFileOrStdin(const std::string& path)
{
    if(path.empty())
    {
        std::string out, line;
          while (std::cin >> line) {
            out += line + "\n";
          }
          return out;
    }
    else
    {
        return FileIO::readFile(path);
    }
}

void writeToFileOrStdout(const std::string& path, const std::string& message)
{
    if(path.empty())
    {
        std::cout << message << "\n";
    }
    else
    {
        FileIO::writeFile(path, message);
    }
}

int main(int argc, char** argv)
{
    try
    {

        auto args = docopt::docopt(usage, {argv + 1, argv + argc}, true, {}, true);

		
        std::string outputFormat = args["--format"].asString();
        if(outputFormat != "xml")
            throw std::runtime_error("Unsupported output format. Currently only xml is supported.");

        std::string input = readFromFileOrStdin(args["--input-file"].asString());
        std::string outputFilePath = args["--output-file"].asString();

        std::istringstream inputStream(input);
        std::ostringstream outputStream;

        fabula::parsing::Parser* parser = fabula::parsing::Parser::create(inputStream, args["--input-file"].asString());
        parser->parse();
        fabula::parsing::XmlWriter writer(outputStream);
        parser->write(writer);
        fabula::parsing::Parser::destroy(parser);

        writeToFileOrStdout(outputFilePath, outputStream.str());
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
