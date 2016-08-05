#pragma once
#include "LexerState.h"
#include <stack>

namespace fabula
{
    namespace parsing
    {
        class LexerInclusionGraph
        {
            std::stack<LexerState> mStack;

        public:

            LexerInclusionGraph(const Lexerstate& initialState)
            {
                ms
            }

            LexerState& push(const LexerState& state)
            {
                mStack.push(state);
            }

            LexerState& pop(const LexerState& state)
            {
                LexerState state = std::move(top());
                mStack.pop();
            }

            LexerState& top()
            {
                return mStack.top();
            }
        };
    }
}
