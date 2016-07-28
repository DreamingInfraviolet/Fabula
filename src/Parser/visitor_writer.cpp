#include "visitor_writer.h"
#include "parse_nodes.h"
#include <cassert>
#include "util.h"

namespace fabula
{
    namespace parsing
    {
        VisitorWriter::VisitorWriter(Writer& w)
            : writer(w) {}

        void VisitorWriter::visit(node::Scene& in)
        {
            writer.push("scene", { {"name", in.name} });

            visit(*in.header);

            if(in.choices.size())
            {
                writer.push("choices");
                for (auto& choice : in.choices)
                {
                    assert(choice);
                    visit(*choice);
                }
                writer.pop();
            }

            if (in.destination)
                visit(*in.destination);

            writer.pop();
        }

        void VisitorWriter::visit(node::Section& in)
        {
            writer.push("section", { { "name", in.name } });

            for (auto it = in.scenes.begin(); it != in.scenes.end(); ++it)
			{
				assert(it->second);
				visit(*it->second);
			}
            for (auto it = in.subsections.begin(); it != in.subsections.end(); ++it)
			{
				assert(it->second);
				visit(*it->second);
			}

			writer.pop();
        }

        void VisitorWriter::visit(node::String& in)
        {
            writer.push("string");
            writer.writeBytes(in.string);
            writer.pop();
        }

        void VisitorWriter::visit(node::Header& in)
        {
            writer.push("header");
            visit(in.title);
            visit(in.description);
            writer.pop();
        }

        void VisitorWriter::visit(node::Destination& in)
        {
            writer.push("destination");
            for (auto it = in.begin(); it != in.end(); ++it)
			{
                writer.push("link");
                writer.writeBytes(*it);
                writer.pop();
            }
            writer.pop();
        }

        void VisitorWriter::visit(node::Choice& in)
        {
            writer.push("choice");
            visit(*in.header);
            visit(*in.destination);
            writer.pop();
        }
    }
}
