#include "parse_tree_visitor.h"
#include "parse_nodes.h"
#include <cassert>


namespace fabula
{
    namespace parsing
    {
        void ParseTreeVisitor::visit(node::Scene& in)
        {
            visit(*in.header);

            if (in.choices.size())
                for (auto& choice : in.choices)
                {
                    assert(choice);
                    visit(*choice);
                }

            if (in.destination)
            {
                visit(*in.destination);
            }
        }

        void ParseTreeVisitor::visit(node::Section& in)
        {
            for (auto& scene : in.scenes)
            {
                assert(scene.second);
                visit(*scene.second);
            }
            for (auto& section : in.subsections)
            {
                assert(section.second);
                visit(*section.second);
            }
        }

        void ParseTreeVisitor::visit(node::String& in)
        {

        }

        void ParseTreeVisitor::visit(node::Header& in)
        {
            visit(in.title);
            visit(in.description);
        }

        void ParseTreeVisitor::visit(node::Destination& in)
        {

        }

        void ParseTreeVisitor::visit(node::Choice& in)
        {
            visit(*in.header);
            visit(*in.destination);
        }
    }
}
