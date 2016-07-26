#include "fparser.h"
#include "log.h"
#include <istream>
#include <ostream>
#include <cassert>
#include "section.h"
#include "FlexLexer.h"
#include <atomic>
#include "visitor_parent_binder.h"
#include "visitor_semantic_checker.h"
#include "visitor_writer.h"
#include "parse_exception.h"

extern int fyyparse();
static yyFlexLexer lexer;

int fyylex()
{
    return lexer.yylex();
}

namespace fabula
{
    namespace parsing
    {
        Parser* Parser::mInstance = nullptr;

        Parser::Parser(std::istream& inputStream, const std::string& rootPath)
            :  mParseTree(nullptr)
        {
            setInputStream(inputStream, rootPath);
        }

        Parser::~Parser()
        {
            //Check that we are disposing of the object properly.
            if (mInstance)
                Log::w("Destroying parser without using the destroy() method is dangerous.",
                    Log::Severity::Medium, Log::Type::Internal);
            if (mParseTree)
                delete mParseTree;
        }

        Parser* Parser::create(std::istream& inputStream, const std::string& rootPath)
        {
            if (mInstance)
            {
                Log::w("Attempting to create multiple parser instances. Returning original.",
                    Log::Severity::Low, Log::Type::Internal);
                return mInstance;
            }
            else
                return mInstance = new Parser(inputStream, rootPath);
        }

        void Parser::destroy(Parser* parser)
        {
            Parser* inst = mInstance;
            mInstance = nullptr;
            delete inst;
        }

        Parser* Parser::instance()
        {
            return mInstance;
        }

        void Parser::setInputStream(std::istream& inputStream, const std::string& rootPath)
        {
            mRootPath = rootPath;
            lexer.yyrestart(&inputStream);
        }

        void Parser::parse()
        {
            static std::atomic<bool> wasAlreadyParsing;
            wasAlreadyParsing = false;

            if (wasAlreadyParsing)
                assert(false);
            else
                wasAlreadyParsing = true;

            fyyparse();
            if (mParseTree)
            {
                VisitorParentBinder vp;
                VisitorSemanticChecker vs;
                vp.visit(*mParseTree);
                vs.visit(*mParseTree);
            }
            else
            {
                throw ParseException("Failed Parsing");
            }

            wasAlreadyParsing = false;
        }

        void Parser::setParseResult(fabula::parsing::node::Section* result)
        {
            if (mParseTree)
                delete mParseTree;
            mParseTree = result;
        }

        node::Section* Parser::getParseResult()
        {
            return mParseTree;
        }

        void Parser::write(Writer& writer)
        {
            if (mParseTree)
            {
                VisitorWriter vw(writer);
                vw.visit(*mParseTree);
            }
        }
    }
}
