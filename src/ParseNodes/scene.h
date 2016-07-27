#pragma once

/**
  * @author Anima Seteine
  * @purpose A node to store information about a scene.
  */


#include <vector>
#include <string>
#include <memory>
#include "parse_node.h"

namespace fabula
{
	namespace parsing
	{
		namespace node
		{
            namespace detail
            {
                struct ParseStageDestination;
            }

            class Section;
			class Choice;
			class Header;
			class Destination;

			class Scene : public ParseNode
			{
            public:
                std::string                          name;
                std::shared_ptr<Header>              header;
                std::vector<std::shared_ptr<Choice>> choices;
                std::shared_ptr<Destination>         destination;

                /** Initialises a fully empty scene. */
                Scene();

                /** Initialises a scene with the given choices, taking ownership of the arguments. */
                Scene(std::vector<std::shared_ptr<Choice>> choices);

                /** Initialises a scene from a destination, taking ownership of the argument. */
                Scene(std::shared_ptr<Destination> destination);

                /** Initialises a scene from a parse destination container. */
                Scene(std::shared_ptr<detail::ParseStageDestination> container);

			    /** Returns true if the scene does not have an outgoing path. */
                bool final() const;

				/** Returns the corresponding node type of the class. */
                virtual NodeType nodeType();
			};
		}
	}
}
