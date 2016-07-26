#pragma once

/**
* @author Anima Seteine
* @purpose This interface represents a class that is capable of saving the parse tree
*          into a file.
*/

#include <string>

namespace fabula
{
	namespace parsing
	{
		class Writer
		{
		protected:
			std::ostream& stream;

		public:

			Writer(std::ostream& stream_)
				: stream(stream_) {}

			/** Enters a new internal scope, given a name. */
			virtual void push(const std::string& name,
				const std::initializer_list<const std::pair<const std::string, const std::string>>& attributes = {}) = 0;
			/** Writes the data of a node. */
			virtual void writeBytes(const std::string& bytes) = 0;
			/** Returns to the previous scope. */
			virtual void pop() = 0;
		};
	}
}

