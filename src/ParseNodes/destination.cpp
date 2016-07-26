#include "destination.h"
#include <cassert>
#include "scene.h"
#include "section.h"
#include "parse_exception.h"
#include "choice.h"
#include "util.h"
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
//			Destination::Destination() {}

//			Destination::Destination(std::string location)
//				: mLocationChain(1, location) {}

//			void Destination::appendLocation(const std::string& location)
//			{
//				mLocationChain.push_back(location);
//			}

//            void Destination::appendLocationFront(const std::string& location)
//            {
//                mLocationChain.push_front(location);
//            }

//			ParseNode::NodeType Destination::nodeType()
//			{
//				return NodeType::Destination;
//			}

//            Scene* getParentScene()
//            {
//                //Get parent scene. We may be in a choice, or not! Remember that this is
//                //a location node as typed inside a scene.
//                Scene* parentScene;

//                if (parent()->nodeType() == ParseNode::NodeType::Choice)
//                {
//                    Choice* parentChoice = dynamic_cast<Choice*>(parent());
//                    assert(parentChoice && parentChoice->parent());
//                    parentScene = dynamic_cast<Scene*>(parentChoice->parent());
//                }
//                else if (parent()->nodeType() == ParseNode::NodeType::Scene)
//                    parentScene = dynamic_cast<Scene*>(parent());
//                else
//                    assert(false);
//            }

//			Scene * Destination::getScene(bool throwSemanticException)
//			{
//#define CONDITIONAL_THROW(message) if (throwSemanticException) throw SemanticException(message); else return nullptr

//				//Get the start node
//				Section* currentNode = nullptr;

//				assert(parent());

//                Scene* parentScene = getParentScene();

//				assert(parentScene && parentScene->parent());
//				Section* parentSection = dynamic_cast<Section*>(parentScene->parent());
//				assert(parentSection);

//                //Go to the root
//                currentNode = parentSection;
//                ParseNode* next = parentSection->parent();

//                while (next != nullptr)
//                {
//                    currentNode = dynamic_cast<Section*>(next);
//                    assert(currentNode);
//                    next = next->parent();
//                }


//				//Now that we have the start, we need to traverse the location chain.
//				assert(mLocationChain.size());

//				for (auto it = mLocationChain.begin(); it != mLocationChain.end() - 1; ++it)
//				{
//					Section* previous = currentNode;
//					currentNode = currentNode->getSubsection(*it);
//					if (!currentNode)
//						CONDITIONAL_THROW("Invalid location: Subsection " + *it +
//							" does not exist in " + previous->name());
//				}

//				//Get and check the final thing on the chain, which is supposed to be a scene.
//				std::string sceneName = mLocationChain.back();
//				Scene* scene = currentNode->getScene(sceneName);

//				if (!scene)
//					CONDITIONAL_THROW("Invalid location: Scene " + sceneName +
//						"does not exist in " + currentNode->name());

//				return scene;

//#undef CONDITIONAL_THROW
//			}

//			std::vector<std::string>::iterator Destination::begin()
//			{
//				return mLocationChain.begin();
//			}

//			std::vector<std::string>::iterator Destination::end()
//			{
//				return mLocationChain.end();
//			}


//            namespace detail
//            {
//                Destination parseDestinationFromContainer(std::shared_ptr<DestinationContainer> container, Section* section)
//                {
//                    assert(container);

//                    ParseNode* prev = section;
//                    assert(prev);

//                    {
//                        ParseNode* current = prev;

//                        while(container->backsteps > 0 && current != nullptr)
//                        {
//                            prev = current;
//                            current = current->parent();
//                        }
//                    }

//                    assert(prev);

//                    if(relative)
//                    {
//                        //If this is a relative path, we must append all the nodes from the root
//                        //onwards.

//                        while(prev != nullptr)
//                        {
//                            Section* sec = dynamic_cast<Section*>(prev);
//                            assert(sec);
//                            dest.appendLocationFront(sec->getName());
//                        }
//                    }
//                }
//            }
		}
	}
}
