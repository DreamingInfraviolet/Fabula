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
                struct DestinationContainer;
            }

            class Section;
			class Choice;
			class Header;
			class Destination;

			class Scene : public ParseNode
			{
                std::string                          mName;
                std::shared_ptr<Header>              mHeader;
                std::vector<std::shared_ptr<Choice>> mChoices;
                std::shared_ptr<Destination>         mDestination;

			public:

				/** Initialises a fully empty scene. */
			    Scene();

			    /** Initialises a scene with the given choices, taking ownership of the arguments. */
                Scene(std::vector<std::shared_ptr<Choice>> choices);

                /** Initialises a scene from a destination, taking ownership of the argument. */
                Scene(std::shared_ptr<Destination> destination);

                /** Initialises a scene from a parse destination container. */
                Scene(std::shared_ptr<detail::DestinationContainer> container);

			    /** Destroys all nested nodes. */
			    ~Scene();

			    /** Sets the header of the scene, taking ownership of the argument. */
                void header(std::shared_ptr<Header> content);

			    /** Sets the current name of the scene. */
			    void name(const std::string& str);

			    /** Returns true if the scene does not have an outgoing path. */
			    bool final() const;

			    /** Returns the current name of the scene. */
			    std::string name() const;

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Returns the header of the scene. */
				Header& header();

                /** Returns the choices. */
                decltype(mChoices)& choices();

				/** Returns the optional destination of the scene. May be null. */
                decltype(mDestination) destination();
			};
		}
	}
}
