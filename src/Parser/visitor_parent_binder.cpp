#include "visitor_parent_binder.h"
#include "parse_nodes.h"
#include <cassert>


namespace fabula
{
    namespace parsing
    {
        void VisitorParentBinder::visit(node::Scene& in)
        {
            in.header->parent(&in);
            visit(*in.header);

            for (auto& choice : in.choices)
            {
                assert(choice);
                choice->parent(&in);
                visit(*choice);
            }

            if (in.destination)
            {
                in.destination->parent(&in);
                ParseTreeVisitor::visit(*in.destination);
            }
        }

        void VisitorParentBinder::visit(node::Section& in)
        {
            for (auto it = in.scenes.begin(); it != in.scenes.end(); ++it)
            {
                assert(it->second);
                it->second->parent(&in);
                visit(*it->second);
            }
            for (auto it = in.subsections.begin(); it != in.subsections.end(); ++it)
            {
                assert(it->second);
                it->second->parent(&in);
                visit(*it->second);
            }
        }

        void VisitorParentBinder::visit(node::Header& in)
        {
            in.title.parent(&in);
            in.description.parent(&in);
            ParseTreeVisitor::visit(in);
        }

        void VisitorParentBinder::visit(node::Choice& in)
        {
            in.header->parent(&in);
            in.destination->parent(&in);
            visit(*in.header);
            ParseTreeVisitor::visit(in);
        }
    }
}
