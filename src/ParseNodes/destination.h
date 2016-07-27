#pragma once

/**
  * @author Anima Seteine
  * @purpose Holds basic information about a destination.
  *          This information is relative to the parse tree, and may be invalid during parsing.
  */

#include <vector>
#include <deque>
#include <string>
#include <memory>
#include "parse_node.h"

namespace fabula
{
    namespace parsing
    {
		class Writer;

        namespace node
        {
			class Scene;
            class Section;

			class Destination : public ParseNode
			{
                std::deque<std::string> mLocationChain;
			public:

				/** Initialises an empty destination . */
				Destination();

				/** Constructs a destination with the given location in the chain. */
				Destination(std::string location);

				/** Appends the inputted location onto the location chain. */
				void appendLocation(const std::string& location);

                /** Appends a location from the front */
                void prependLocation(const std::string& location);

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Returns the pointer to a scene if one exists, inferred from the destination.
				  * Assumes that parent has been bound.
				  * Throws a SemanticException if requested ^_^ Otherwise returns null upon failure. */
				Scene* getScene(bool throwSemanticException = false);

                /** Returns the parent scene. */
                Scene* getParentScene();

				/** Returns an iterator to the start of the destination chain. */
				std::vector<std::string>::iterator begin();

				/** Returns an iterator to the end of the destination chain. */
				std::vector<std::string>::iterator end();

                decltype(mLocationChain)& _getLocationChain()
                {
                    return mLocationChain;
                }
			};

            namespace detail
            {
                //<backsteps, relative, destination>
                struct DestinationContainer
                {
                    int backsteps;
                    bool relative;
                    Destination destination;
                    DestinationContainer(int backsteps, bool relative, Destination destination)
                        : backsteps(backsteps), relative(relative), destination(destination) {}
                };

                Destination parseDestinationFromContainer(std::shared_ptr<DestinationContainer> container, Section* section);
            }
		}
	}
}
