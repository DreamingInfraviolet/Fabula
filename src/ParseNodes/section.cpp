#include "section.h"
#include "scene.h"
#include <cassert>
#include "parse_exception.h"
#include <set>
#include "parse_tree_visitor.h"
#include "parse_exception.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
            void Section::add(const std::shared_ptr<Scene>& s)
            {
                assert(s);
                if (hasChildWithName(s->name))
                    throw SemanticException("An object with this name already exists.");
                scenes[s->name] = s;
            }

            void Section::add(const std::shared_ptr<Section>& s)
            {
                assert(s);
                if (hasChildWithName(s->name))
                    throw SemanticException("An object with this name already exists.");
                subsections[s->name] = s;
            }

            ParseNode::NodeType Section::nodeType()
            {
                return NodeType::Section;
            }

            Scene* Section::findStartScene()
            {
                return getScene("main", true);
            }

            bool Section::hasChildWithName(const std::string& name, bool recursive)
            {
                return getSubsection(name, recursive) || hasScene(name, recursive);
            }
        }
    }
}
