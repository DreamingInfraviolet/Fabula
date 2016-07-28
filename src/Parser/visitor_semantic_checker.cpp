#include "visitor_semantic_checker.h"
#include "parse_nodes.h"
#include <cassert>
#include "parse_exception.h"

namespace fabula
{
    namespace parsing
    {
        void VisitorSemanticChecker::visit(node::Scene& in)
        {
            if (in.name == "main")
			{
				++mNumberOfStartPointsFound;
				if (mNumberOfStartPointsFound > 1)
					throw SemanticException("Multiple 'main' scenes found.");
			}

			ParseTreeVisitor::visit(in);
        }

        void VisitorSemanticChecker::visit(node::Section& in)
        {
            //In this rather unique scenario, the semantics are guaranteed to be already checked
            //due to how the values are stored in a map for efficiency and were checked beforehand ^.^
            //We only need to visit the other nodes.

            ParseTreeVisitor::visit(in);

			//If this is the final section and we haven't found a main scene:
			if (in.parent() == nullptr && !mNumberOfStartPointsFound)
			{
				throw SemanticException("No 'main' scene found.");
			}
        }

        void VisitorSemanticChecker::visit(node::Destination& in)
        {
            in.getScene(true);
        }
    }
}
