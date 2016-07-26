#pragma once
#include "parse_tree_visitor.h"
#include "writer.h"

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

        class VisitorWriter : public ParseTreeVisitor
        {
            Writer& writer;

            public:
                VisitorWriter(Writer& w);

                virtual void visit(node::Scene& in);
                virtual void visit(node::Section& in);
                virtual void visit(node::String& in);
                virtual void visit(node::Header& in);
                virtual void visit(node::Destination& in);
                virtual void visit(node::Choice& in);
        };
    }
}