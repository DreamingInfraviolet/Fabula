#pragma once
#include <string>
#include <memory>
#include "Poco/Path.h"

namespace fabula
{
    namespace parsing
    {
        struct LexerState
        {
			Poco::Path filePath;
            int lineNumber = 0;
            std::istream* inputStream = nullptr;

            LexerState(const std::string& absoluteFilePath = "", int lineNumber = 0, std::istream* inputStream = nullptr)
                : lineNumber(lineNumber), inputStream(inputStream)
            {
				filePath = absoluteFilePath;
            }

			std::string getAbsolutePathFromRelative(const std::string& relative) const
			{
				auto dir = Poco::Path(filePath).absolute().setFileName("");
				auto ret = dir.append(Poco::Path(relative)).toString();
				return ret;
			}
        };
    }
}
