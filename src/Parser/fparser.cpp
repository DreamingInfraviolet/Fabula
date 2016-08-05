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
#include "lexer_include_graph.h"

extern int fyyparse();
extern fabula::parsing::LexerIncludeGraph gLexerIncludeGraph;

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

        Parser::Parser(std::istream* inputStream, const std::string& rootPath)
        {
            setInputStream(inputStream, rootPath);
        }

        void Parser::initLexerState()
        {
            gLexerIncludeGraph.clear();
            LexerState state;
            state.absoluteFilePath = mRootPath;
            state.fileName = mRootPath; //@TODO: change this to something more readable
            state.inputStream = mInputStream;
            gLexerIncludeGraph.push(std::move(state));
        }

        Parser::~Parser()
        {
            //Check that we are disposing of the object properly.
            if (mInstance)
                Log::w("Destroying parser without using the destroy() method is dangerous.",
                    Log::Severity::Medium, Log::Type::Internal);
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
                return mInstance = new Parser(&inputStream, rootPath);
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

        void Parser::setInputStream(std::istream* inputStream, const std::string& rootPath)
        {
            mInputStream = inputStream;
            mRootPath = rootPath;
            lexer.yyrestart(inputStream);
        }

        void Parser::parse()
        {
            static std::atomic<bool> wasAlreadyParsing;
            wasAlreadyParsing = false;

            if (wasAlreadyParsing)
                assert(false);
            else
                wasAlreadyParsing = true;

            initLexerState();
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

        void Parser::setParseResult(std::shared_ptr<fabula::parsing::node::Section> result)
        {
            mParseTree = std::move(result);
        }

        node::Section* Parser::getParseResult()
        {
            return mParseTree.get();
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
