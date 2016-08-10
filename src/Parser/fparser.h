#pragma once

/**
* @author Anima Seteine
* @purpose The main parsing interface. This class is what's responsible for parsing an input stream and presenting
*          the parse tree after error checking.
*/

#include <string>
#include <istream>
#include <ostream>
#include <memory>

namespace fabula
{
    namespace parsing
    {
		namespace node { class Section; }
		class Writer;

        class Parser
        {
        private:

            static Parser* mInstance;

            std::shared_ptr<fabula::parsing::node::Section> mParseTree; //Represents the current internal tree
            std::string mRootPath;
            std::istream* mInputStream = nullptr;

            Parser(std::istream* inputStream, const std::string& rootPath);

            void initLexerState();

            ~Parser();

        public:
            /** Creates a new parser given an input stream and the directory from which it
              * should parse. The directory is not used yet, but is placed here for future
              * compatability to allow recursive scripts.
              * Only one parser may exist at a time, and must be destroyed to free memory. */
            static Parser* create(std::istream& inputStream, const std::string& rootPath = "");

            /** Destroys the current parser, freeing memory. */
            static void destroy(Parser* parser);

            /** Returns the current parser instance. */
			static Parser* instance();

            /** Changes the input stream and directory. */
            void setInputStream(std::istream* inputStream, const std::string& rootPath);

            /** Parses with the current stream. Note that only one parsing session may be run
              * at a time! Checks semantics as well. May throw a SyntacticException, SemanticException,
			  * or an arbitrary exception upon an internal error. */
            void parse();

			/** Sets the parse result. Should only be used by the generated parser. */
            void setParseResult(std::shared_ptr<node::Section> result);

			/** Returns the parse result. */
			node::Section* getParseResult();

			/** Writes the parse tree to a stream. */
			void write(Writer& writer);
        };
    }
}
