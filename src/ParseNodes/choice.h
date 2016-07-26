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
                std::shared_ptr<Header>      mHeader      = nullptr;
                std::shared_ptr<Destination> mDestination = nullptr;
        	public:

        		/** Initialises a choice, taking ownership of the arguments. */
                Choice(const std::shared_ptr<Header>& header, const std::shared_ptr<Destination>& destination);

                /** Destroys the choice, deleting the children. */
        		~Choice();

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Returns the internal header. */
                decltype(mHeader)& header();

				/** Returns the internal destination. */
                decltype(mDestination)& destination();
            };
        }
    }
}
