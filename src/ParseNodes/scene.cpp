#include "scene.h"
#include "header.h"
#include "choice.h"
#include "destination.h"
#include <cassert>
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
//            Scene::Scene() {}

//            Scene::Scene(std::vector<std::shared_ptr<Choice> > choices)
//                : mChoices(choices) {}

//            Scene::Scene(std::shared_ptr<Destination> destination)
//                : mDestination(destination) {}

//            Scene::Scene(std::shared_ptr<detail::DestinationContainer> container)
//            {
//                assert(container);
//                if(container->relative)
//                {
//                    container->destination.parent(this);
//                }
//            }

//            Scene::~Scene()
//            {
//                if (mChoices)
//                    for (Choice* c : *mChoices)
//                        delete c;
//                delete mChoices;
//                delete mHeader;
//                delete mDestination;
//            }

//            bool Scene::final() const
//            {
//                return mChoices == nullptr && mDestination == nullptr;
//            }

//			ParseNode::NodeType Scene::nodeType()
//			{
//				return NodeType::Scene;
//			}
        }
    }
}
