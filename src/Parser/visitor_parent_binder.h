#pragma once
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
            class Scene;
            class Section;
            class String;
            class Header;
            class Destination;
        }

        class VisitorParentBinder : public ParseTreeVisitor
        {
            public:
                virtual void visit(node::Scene& in);
                virtual void visit(node::Section& in);
                virtual void visit(node::Header& in);
                virtual void visit(node::Choice& in);
        };
    }
}
