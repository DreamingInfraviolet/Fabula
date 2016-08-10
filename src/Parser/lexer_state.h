#pragma once
#include <string>
#include <memory>

namespace fabula
{
    namespace parsing
    {
        struct LexerState
        {
            std::string fileName;
			std::string directoryPath;
            std::string absoluteFilePath;
            int lineNumber = 0;
            std::istream* inputStream = nullptr;

            LexerState(const std::string& absoluteFilePath = "", int lineNumber = 0, std::istream* inputStream = nullptr)
                : lineNumber(lineNumber), inputStream(inputStream), absoluteFilePath(absoluteFilePath)
            {
				fileName = getPathFilename(absoluteFilePath);
				directoryPath = getFileDirectory(absoluteFilePath);
            }

			//Temporary solutions

			std::string joinPaths(const std::string& a, const std::string& b)
			{
				std::string answer;
				//If b is absolute
				if ((b.size() > 1 && (b[0] == '/' || b[0] == '\\')) || (b.size() > 1 && (isalnum(b[0]) && b[1] == ':')))
					return b;
				else
					return a + "/" + b;
			}

			std::string getPathFilename(const std::string& path)
			{
				auto pos1 = path.rfind("/");
				auto pos2 = path.rfind("\\");
				if (pos1 == std::string::npos && pos2 == pos1)
					return path;
				if (pos1 == std::string::npos)
					pos1 = pos2;
				
				return path.substr(pos1);
			}

			std::string getFileDirectory(const std::string& path)
			{
				auto pos1 = path.rfind("/");
				auto pos2 = path.rfind("\\");
				if (pos1 == std::string::npos && pos2 == pos1)
					return path;
				if (pos1 == std::string::npos)
					pos1 = pos2;

				return path.substr(0, path.size() - pos1 - 1);
			}
        };
    }
}
