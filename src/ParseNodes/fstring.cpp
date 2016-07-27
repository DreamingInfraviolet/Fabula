#include "fstring.h"
#include "parse_tree_visitor.h"
#include "parse_exception.h"
#include <boost/regex.hpp>
#include <fstream>

namespace
{
//    std::regex rxCompileTimeMixin(""); // Not implemented
//    std::regex rxRunTimeMixin(""); // Not implemented
    boost::regex rxCompileTimeFileMixin("\\$\\[[a-zA-Z\\.\\/\\\\]\\]");
}

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
//            String::String() {}

//            String::String(const std::string& string) : _str(string) { prepareString(); }

//            String::String(const char* string) : _str(string) { prepareString(); }

//			ParseNode::NodeType String::nodeType()
//			{
//				return NodeType::String;
//			}

//            std::string modifyStr (const boost::smatch& match)
//            {
//                std::string str = match.str();
//                auto begin = str.find("[") + 1;
//                auto end = str.rfind("]");
//                assert(begin != std::string::npos && end != std::string::npos);

//                std::string filePath = str.substr(begin, end-begin);

//                std::ifstream file(filePath);

//                if(!file)
//                    throw ParseException(std::string("Unable to open file ") + filePath);

//                std::string line;
//                std::string out;
//                while(getline(file, line))
//                    out += line + "\n";
//                return out;
//            }

//            void String::prepareString()
//			{
//				//Remove quotation marks:
//				_str = std::string(_str.begin() + 1, _str.end() - 1);

//                //Replace references to files with file contents
//                boost::regex_replace(_str, rxCompileTimeFileMixin,"hi");

//                /* Doesn't seem to work.. Will fix later
//				size_t pos;
//				while ((pos = _str.find("\\\"") != std::string::npos))
//					_str.replace(pos, 2, "\"");
//				while ((pos = _str.find("\\\'") != std::string::npos))
//					_str.replace(pos, 2, "\'");
//                */
//            }

        }
    }
}
