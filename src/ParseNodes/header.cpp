#include "header.h"
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
            Header::Header() {}

            Header::Header(const String& s1, const String& s2)
                : title(s1), description(s2) {}

            ParseNode::NodeType Header::nodeType()
            {
                return NodeType::Header;
            }
        }
    }
}
