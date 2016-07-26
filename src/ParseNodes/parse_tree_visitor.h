#pragma once

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
            class Choice;
        }

        class ParseTreeVisitor
        {
            public:
                virtual void visit(node::Scene& in);
                virtual void visit(node::Section& in);
                virtual void visit(node::String& in);
                virtual void visit(node::Header& in);
                virtual void visit(node::Destination& in);
                virtual void visit(node::Choice& in);
        };
    }
}
