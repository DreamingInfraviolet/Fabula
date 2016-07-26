#pragma once
#include <string>

namespace fabula
{
	namespace parsing
	{
		class ParseException : public std::exception
		{
		public:
			std::string message;
			int line;

			ParseException() {}
			ParseException(const std::string& message_)
				: message(message_) {}
		};

		class SyntacticException : public ParseException
		{
		public:
			SyntacticException() : ParseException() {}
			SyntacticException(const std::string& message_)
				: ParseException(message_) {}
		};

		class SemanticException : public ParseException
		{
		public:
			SemanticException() : ParseException() {}
			SemanticException(const std::string& message_)
				: ParseException(message_)  {}
		};
	}
}