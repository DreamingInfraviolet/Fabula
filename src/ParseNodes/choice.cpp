#include "choice.h"
#include "header.h"
#include "destination.h"
#include <cassert>
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
            Choice::Choice(const std::shared_ptr<Header>& header, const std::shared_ptr<Destination>& destination)
                    : header(header), destination(destination) {}

            ParseNode::NodeType Choice::nodeType()
            {
                return NodeType::Choice;
            }
        }
    }
}
