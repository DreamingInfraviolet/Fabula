#pragma once
#include <string>
#include <stdexcept>

namespace fabula
{
	namespace parsing
	{
#define BASIC_EXCEPTION(NAME)
        class NAME : public std::runtime_error
        {
        public:
            NAME() : std::runtime_error("") {}
            NAME(const std::string& message_)
                : std::runtime_error(message_) {}
        };

        BASIC_EXCEPTION(ParseException)
        BASIC_EXCEPTION(SynstacticException)
        BASIC_EXCEPTION(SemanticException)
#undef BASIC_EXCEPTION
	}
}
