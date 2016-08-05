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
            void Destination::appendLocation(const std::string& location)
            {
                mLocationChain.push_back(location);
            }

            void Destination::prependLocation(const std::string& location)
            {
                mLocationChain.push_front(location);
            }

            ParseNode::NodeType Destination::nodeType()
            {
                return NodeType::Destination;
            }

            Scene* Destination::getParentScene()
            {
                //Get parent scene. We may be in a choice, or not!

                Scene* answer = nullptr;
                assert(parent());

                if (parent()->nodeType() == ParseNode::NodeType::Choice)
                {
                    auto parentChoice = dynamic_cast<Choice*>(parent());
                    assert(parentChoice);
                    answer = dynamic_cast<Scene*>(parentChoice->parent());
                }
                else if (parent()->nodeType() == ParseNode::NodeType::Scene)
                    answer = dynamic_cast<Scene*>(parent());
                else
                    assert(false);

                assert(answer);
                return answer;
            }

            Scene* Destination::getScene(bool throwSemanticException)
            {
#define CONDITIONAL_THROW(message) if (throwSemanticException) throw SemanticException(message); else return nullptr

                if(!mLocationChain.size())
                    CONDITIONAL_THROW("Invalid location: it is empty.");

                //Get the start node
                Scene* parentScene = getParentScene();

                assert(parentScene);
                Section* parentSection = dynamic_cast<Section*>(parentScene->parent());
                assert(parentSection);

                //We need to traverse the location chain.
                const auto root = dynamic_cast<Section*>(parentSection->getRoot());
                if(!root)
                    CONDITIONAL_THROW("Invalid state when searching for root.");

                auto currentNode = root;
                for (auto it = mLocationChain.begin(); it != mLocationChain.end() - 1; ++it)
                {
                    auto previous = currentNode;
                    currentNode = currentNode->getSubsection(*it);
                    if (!currentNode)
                        CONDITIONAL_THROW("Invalid location: Subsection " + *it +
                            " does not exist in " + previous->name);
                }

                //Get and check the final thing on the chain, which is supposed to be a scene.
                std::string sceneName = mLocationChain.back();
                Scene* scene = currentNode->getScene(sceneName);

                if (!scene)
                    CONDITIONAL_THROW("Invalid location: Scene " + sceneName +
                        " does not exist in " + currentNode->name);

                return scene;

#undef CONDITIONAL_THROW
            }

            decltype(Destination::mLocationChain)::iterator Destination::begin()
            {
                return mLocationChain.begin();
            }

            decltype(Destination::mLocationChain)::iterator Destination::end()
            {
                return mLocationChain.end();
            }
		}
	}
}
