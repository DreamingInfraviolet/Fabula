#pragma once

/**
  * @author Anima Seteine
  * @purpose This represents an enhanced string class that stores strings that support special Fabula formatting.
  */

#include <string>
#include <vector>
#include "parse_node.h"


namespace fabula
{
    namespace parsing
    {
		class Writer;

        namespace node
        {
            class String : public ParseNode
            {
                std::string _str;
            public:

                /** Constructs the empty string. */
        		String();

                /** Constructs the string from a std::string. */
                String(const std::string& string);

                /** Constructs the string from a character pointer. */
        		String(const char* string);

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Tidies the string, clening \", etc. */
                void prepareString();

				/** Returns the internal string. */
				std::string& string();
            };
        }
    }
}
