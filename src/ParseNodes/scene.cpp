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
            Scene::Scene() {}

            Scene::Scene(std::vector<std::shared_ptr<Choice> > choices)
                : choices(choices) {}

            Scene::Scene(std::shared_ptr<Destination> destination)
                : destination(destination) {}

            bool Scene::final() const
            {
                return choices.size() == 0 && !destination;
            }

            ParseNode::NodeType Scene::nodeType()
            {
                return NodeType::Scene;
            }
        }
    }
}
