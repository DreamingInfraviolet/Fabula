#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
#include <algorithm>
#include <regex>
#include "section.h"
#include "xml_writer.h"
#include "scene.h"
#include "fparser.h"
#include "header.h"
#include "choice.h"
#include "docopt.h"
#include "util.h"
#include "destination.h"

using namespace std;
using namespace fabula;
using namespace fabula::parsing;
using namespace fabula::parsing::node;


namespace fabula
{
    struct Configuration
    {
        std::string source;
        std::string templatePath;
        bool verbose = false;
        std::string prefix;
        std::string folder;
    };

    class NameManager
    {
        bool mScrambleNames;
        std::map<Scene*, std::string> nameMapping;
        std::string mPrefix;

        void _generateNames(Section* root)
        {
            assert(root);

            //Go through each subsection
            for (auto s = root->subsections.begin(); s != root->subsections.end(); ++s)
            {
                assert(s->second);
                _generateNames(s->second.get());
            }

            //Register names of each scene
            for (auto s = root->scenes.begin(); s != root->scenes.end(); ++s)
            {
                assert(s->second);
                addName(root, s->second.get());
            }

        }

        void scrambleNames()
        {
            //Generate consecutive numbers and shuffle them
            std::vector<int> numbers;
            numbers.resize(nameMapping.size());
            for (size_t i = 0; i < numbers.size(); ++i)
                numbers[i] = i;

            std::random_shuffle(numbers.begin(), numbers.end());

            //Set random numbers as new names
            int i = 0;
            for (auto mapping = nameMapping.begin(); mapping != nameMapping.end(); ++mapping)
                mapping->second = toString(numbers[i++]);

        }

        void addName(Section* section, Scene* scene)
        {
            assert(section);
            assert(scene);

            Section* next = section;
            std::string prefix = section->name;
            std::string postfix = scene->name;

            while ((next = dynamic_cast<Section*>(next->parent())) != nullptr)
                prefix = next->name + "." + prefix;

            nameMapping[scene] = mPrefix + prefix + postfix;
        }

    public:

        NameManager(bool scrambleNames = true)
            : mScrambleNames(scrambleNames) { }

        void setPrefix(const std::string& prefix)
        {
            mPrefix = prefix;
        }

        void generateNames(Section* root)
        {
            _generateNames(root);
            if (mScrambleNames)
                scrambleNames();

            Scene* start = root->findStartScene();
            assert(start);

            nameMapping[start] = "index";
        }

        std::string getName(Scene* scene)
        {
            return nameMapping[scene] + ".html";
        }

    };

    class HtmlInterface
    {
        NameManager nameManager;
        std::string templateStr;

        std::regex nameRegex;
        std::regex headRegex;
        std::regex descRegex;
        std::regex choicesRegex;

        void handleScene(Scene* scene, Section* parent, const Configuration& config)
        {
            assert(scene);
            assert(parent);

            nameManager.setPrefix(config.prefix);

            std::string fileName = nameManager.getName(scene);

            std::ofstream file(config.folder + fileName);

            if(config.verbose)
                std::cout << "Writing file " << fileName << "\n";

            std::string str(templateStr);

            std::ostringstream choicesStr;
            XmlWriter writer(choicesStr);

            //Write choices
            writer.push("ul");
            for (auto& c : scene->choices)
            {
                Scene* dest = c->destination->getScene();

                writer.push("li");
                writer.push("a", { { "href", nameManager.getName(dest) } });
                writer.push("h3");
                writer.writeBytes(c->header->title.string);
                writer.pop();//h3
                writer.push("h2");
                writer.writeBytes(c->header->description.string);
                writer.pop();//h2
                writer.pop();//a
                writer.pop();//li
            }
            writer.pop();//ul

            str = std::regex_replace(
                std::regex_replace(
                    std::regex_replace(
                        std::regex_replace(
                            str, choicesRegex, choicesStr.str()),
                        descRegex, scene->header->description.string),
                    headRegex, scene->header->title.string),
                nameRegex, scene->name);

            file << str;
        }

        void handleSection(Section* section, const Configuration& config)
        {
            //Write each scene
            for (auto scene = section->scenes.begin(); scene != section->scenes.end(); ++scene)
                handleScene(scene->second.get(), section, config);

            //Handle each subsections
            for (auto s = section->subsections.begin(); s != section->subsections.end(); ++s)
                handleSection(s->second.get(), config);

        }

    public:

        HtmlInterface()
            : nameRegex(R"(\[\$\s*scene_name\s*\$\])"),
              headRegex(R"(\[\$\s*head\s*\$\])"),
              descRegex(R"(\[\$\s*desc\s*\$\])"),
              choicesRegex(R"(\[\$\s*choices\s*\$\])") { }

        void process(Section* root, const Configuration& config)
        {
            nameManager.generateNames(root);
            handleSection(root, config);
        }

        void setTemplateString(const std::string& str)
        {
            templateStr = str;
        }
    };
}

extern int fyydebug;
int main(int argc, const char** argv)
{
    const char* usage =
R"(Usage:
    program [options]
Options:
    -i=<input_file> --input-file=<input_file>      The input file to read from. If not specified, will read from console
    -t=<template_file> --template-file=<template_file>  The template html file to use.
    -o=<output_dir> --output-folder=<output_dir>   The output directory to write to. If not specified, will print to console
    -v --verbose  Provides additional debug messages [default: false]
    -p --prefix  Specifies a prefix to be appended to each output filename [default: ]
)";

    Configuration config;

    try
    {
        auto args = docopt::docopt(usage, {argv + 1, argv + argc}, true, {}, true);

        if(args["--verbose"].asBool())
            config.verbose = true;

        if(!args["--template-file"])
            throw std::runtime_error("No template file provided.");
        else
            config.templatePath = args["--template-file"].asString();

        if(!args["--input-file"])
            throw std::runtime_error("No input Fabula file provided.");
        else
            config.source = args["--input-file"].asString();

        std::string prefix;
        if(args["--prefix"])
            config.prefix = args["--prefix"].asString();

        if(args["--output-folder"])
        {
            config.folder = args["--output-folder"].asString();
            if(!config.folder.empty())
                if(config.folder.back() != '/' && config.folder.back() != '\\')
                    config.folder.push_back('/');
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
        std::cout << usage << "\n";
        return 1;
    }

    fyydebug = 0;
    std::fstream file(config.source);
    if (file.fail())
    {
        std::cout << "Unable to open input fabula file\n";
        return 1;
    }

    std::fstream templateFile(config.templatePath);
    if (templateFile.fail())
    {
        std::cout << "Unable to open template file\n";
        return 2;
    }

    std::string templateStr = std::string(std::istreambuf_iterator<char>(templateFile), std::istreambuf_iterator<char>());

    fabula::parsing::Parser* parser = fabula::parsing::Parser::create(file, "");
    parser->parse();
    //////////////////////////////////////////////////////////////////////////////////////
    HtmlInterface interface;
    interface.setTemplateString(templateStr);
    interface.process(parser->getParseResult(), config);
    //////////////////////////////////////////////////////////////////////////////////////
    fabula::parsing::Parser::destroy(parser);
}
