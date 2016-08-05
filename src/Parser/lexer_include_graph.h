#pragma once
#include "lexer_state.h"
#include <stdexcept>
#include <vector>
#include <set>

namespace fabula
{
    namespace parsing
    {
        class LexerIncludeGraphException : std::runtime_error
        {
        public:
            LexerIncludeGraphException(const std::string& msg) : std::runtime_error(msg) {}
        };

        class LexerIncludeGraph
        {
            std::vector<LexerState> mStack;
        public:

            void push(const LexerState& state)
            {
                if(hasDuplicate(&state))
                    throw LexerIncludeGraphException(std::string("File '") + state.absoluteFilePath + "' <<included>> multiple times.");
                mStack.push_back(state);
            }

            void pop()
            {
                LexerState result = std::move(top());
                mStack.pop_back();
                //If we are not at the root, delete the stream.
                if(mStack.size())
                    delete result.inputStream;
            }

            LexerState& top()
            {
                if(mStack.size())
                    return mStack.back();
                else
                    throw std::runtime_error("Can not get top lexer state: no states.");
            }

            size_t size() const { return mStack.size(); }

            void clear()
            {
                mStack.clear();
            }

            bool hasDuplicate(const LexerState* additionalState = nullptr) const
            {
                std::set<std::string> allFiles;
                for(const auto& state : mStack)
                {
                    if(allFiles.insert(state.absoluteFilePath).second)
                        return true;
                }

                if(additionalState && allFiles.find(additionalState->absoluteFilePath) != allFiles.end())
                    return true;
                return false;
            }
        };
    }
}
