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
            std::string absoluteFilePath;
            int lineNumber = 0;
            std::istream* inputStream = nullptr;

            LexerState(const std::string& fileName = "", const std::string& absoluteFilePath = "", int lineNumber = 0, std::istream* inputStream = nullptr)
                : fileName(fileName), absoluteFilePath(absoluteFilePath), lineNumber(lineNumber), inputStream(inputStream)
            {

            }
        };
    }
}
