%{
 #define YY_NO_UNISTD_H
 #include <string>
 #include <vector>
 #include <iostream>
 #include <memory>
 #include <fstream>
 #include "section.h"
 #include "fstring.h"
 #include "scene.h"
 #include "choice.h"
 #include "header.h"
 #include "destination.h"
 #include "fyystype.h"
 #define FYYSTYPE FYYSType
 extern FYYSTYPE yyltype;
 using namespace fabula::parsing::node;
 #include "generated_parser.hpp"
 #include "lexer_include_graph.h"

 fabula::parsing::LexerIncludeGraph gLexerIncludeGraph;


#define NEWLINE_CALLBACK\
    ++gLexerIncludeGraph.top().lineNumber;

void flexErrorCallback(const std::string& msg)
{
    std::cout << gLexerIncludeGraph.top().lineNumber << ":" << gLexerIncludeGraph.top().fileName << ": " << (msg) << std::endl;
    abort();
}

#define PUSH_FILE(filestr, size){try{\
    BEGIN(INITIAL);\
    /**TODO: Make this nicer */\
	std::string actualPath = gLexerIncludeGraph.top().joinPaths(gLexerIncludeGraph.top().absoluteFilePath, filestr);\
    gLexerIncludeGraph.push(fabula::parsing::LexerState(actualPath, 0, new std::ifstream(actualPath)));\
    if(!gLexerIncludeGraph.top().inputStream || !(*gLexerIncludeGraph.top().inputStream))\
        flexErrorCallback(std::string("Could not open ") + actualPath);\
    yypush_buffer_state(yy_create_buffer(gLexerIncludeGraph.top().inputStream, size));\
	} catch(const std::exception& e) { flexErrorCallback(e.what()); }\
}	

#define POP_FILE(){\
    gLexerIncludeGraph.pop();\
	yypop_buffer_state();\
    if(gLexerIncludeGraph.size()) /* If this is not the root file */ \
        BEGIN(endincl); /* Expect >> */ \
    }
%}

IDENTIFIER [a-zA-Z_]+ ([0-9] | [a-zA-Z_])*

WHITESPACE [ \t\n\r]

%option noyywrap
    //Do not generate a default rule to avoid holes
%option nodefault
    //Generate C++
%option c++

    //Define start condition & co.
%x incl
%x endincl
%%
 
        // Warning: Use double quotes for literals!

"/"       { fyylval.stdstring = "/"; return tdiv; }
"{"       { fyylval.stdstring = "{";  return tbracket_curly_open;  }
"}"       { fyylval.stdstring = "}";  return tbracket_curly_close; }
"["       { fyylval.stdstring = "[";  return tbracket_square_open; }
"]"       { fyylval.stdstring = "]";  return tbracket_square_close; }
"scene"   { fyylval.stdstring = "scene";  return tscene; }
"choice"  { fyylval.stdstring = "choice";  return tchoice; }
"goto"    { fyylval.stdstring = "goto";  return tgoto; }
[A-Za-z_]+([a-za-z0-9_])*       { fyylval.stdstring = yytext;  return tidentifier; }
(\"([^\"\\]|(\\[a-zA-Z\"]))*\")|(\'([^\'\\]|(\\[a-zA-Z\']))*\')  { fyylval.stdstring = yytext;  return tstring; }
"\r\n"      { NEWLINE_CALLBACK }
"\r"      { NEWLINE_CALLBACK }
"\n"      { NEWLINE_CALLBACK }

"<<" BEGIN(incl);
<incl>[0-9a-zA-Z_\.\-/\\ \t:]+ { PUSH_FILE(yytext, YY_BUF_SIZE) }
<incl>.|\n|\r         { flexErrorCallback("Found newline before terminating >>"); BEGIN(INITIAL); }

<endincl>">>"         { BEGIN(INITIAL); }
<endincl>.|\n|\r      { flexErrorCallback(std::string("Expected >> after file inclusion, found '") + yytext + "'"); BEGIN(INITIAL); }

<<EOF>>       {
                  POP_FILE()
                  if (!YY_CURRENT_BUFFER)
                      yyterminate();
              }

[ \t]          /* Ignore */
"."     { fyylval.stdstring = ".";  return tfullstop; }
.       { flexErrorCallback(std::string("Unrecognised symbol at ") + gLexerIncludeGraph.top().fileName + ":" + std::to_string(gLexerIncludeGraph.top().lineNumber)
                            + ": \"" + yytext + "\""); }
%%
