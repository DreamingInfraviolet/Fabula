#pragma once

/**
  * @author Anima Seteine
  * @purpose This represents a "header", which is a title with an optional description.
  *          The description is considered optional if it is not provided, or if it's empty when trimmed.
  */

#include "fstring.h"
#include "parse_node.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
            class Header : public ParseNode
            {
            public:

                String title, description;

                /** Initialises an empty header. */
                Header();

                /** Initialises a header with s1 as title and s2 as description. */
                Header(const String& s1, const String& s2 = String());

				/** Returns the corresponding node type of the class. */
                virtual NodeType nodeType();
            };
        }
    }
}
