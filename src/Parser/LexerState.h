#pragma once
#include <string>
#include <experimental/filesystem>

namespace fabula
{
    namespace parsing
    {
        class LexerState
        {
        public:
            int lineNumber = 0;
            std::string fileName;
            std::istream* fileInputStream = nullptr;
        };
    }
}
