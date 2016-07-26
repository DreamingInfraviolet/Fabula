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

        class VisitorSemanticChecker : public ParseTreeVisitor
        {
			int mNumberOfStartPointsFound = 0;

            public:
                virtual void visit(node::Scene& in);
                virtual void visit(node::Section& in);
                virtual void visit(node::Destination& in);
        };
    }
}
