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
 using namespace fabula::parsing::node;
 #include "generated_parser.hpp"
 #include "fyystype.h"

 std::vector<int> fabulaLineStack(1, 0);
 std::vector<std::unique_ptr<std::istream>> fileStack;

#define NEWLINE_CALLBACK\
    ++fabulaLineStack.back();

void flexErrorCallback(const std::string& msg)
{
    std::cout << fabulaLineStack.back() << ": " << (msg) << std::endl;
    abort();
}

#define PUSH_FILE(filestr, size){\
    BEGIN(INITIAL);\
    fileStack.push_back(std::make_unique<std::ifstream>(filestr));\
    if(!fileStack.back())\
        flexErrorCallback(std::string("Could not open ") + filestr);\
    yypush_buffer_state(yy_create_buffer(fileStack.back().get(), size));\
    fabulaLineStack.push_back(0);\
}

#define POP_FILE(){\
    yypop_buffer_state(); /* Pop buffer */ \
    fabulaLineStack.pop_back(); /* Pop line */ \
    if(fileStack.size()) /* If this is not the root file */ \
        fileStack.pop_back(); /* Pop file */ \
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
<incl>[0-9a-zA-Z_\.\-/\\ \t]+ {std::cerr<<"Found " << yytext << "\n"; PUSH_FILE(yytext, YY_BUF_SIZE) }
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
.       { flexErrorCallback(std::string("Unrecognised symbol at ") + std::to_string(fabulaLineStack.back())
                            + ": \"" + yytext + "\""); }
%%
