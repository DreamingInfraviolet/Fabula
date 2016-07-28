#pragma once

/**
  * @author Anima Seteine
  * @purpose This class holds the information about a single choice option.
  */

#include "parse_node.h"
#include <memory>

namespace fabula
{
    namespace parsing
    {
		class Writer;

        namespace node
        {
            class Header;
            class Destination;

            class Choice : public ParseNode
            {
        	public:

                std::shared_ptr<Header>      header;
                std::shared_ptr<Destination> destination;

                Choice() {}

                /** Initialises a choice. */
                Choice(const std::shared_ptr<Header>& header, const std::shared_ptr<Destination>& destination = nullptr);

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();
            };
        }
    }
}
