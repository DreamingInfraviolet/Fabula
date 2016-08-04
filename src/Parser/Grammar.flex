%{
 #define YY_NO_UNISTD_H
 #include <string>
 #include <vector>
 #include "section.h"
 #include "fstring.h"
 #include "scene.h"
 #include "choice.h"
 #include "header.h"
 #include "destination.h"
 using namespace fabula::parsing::node;
 #include "generated_parser.hpp"
 #include "fyystype.h"

 int flexLineNo=0;
%}

IDENTIFIER [a-zA-Z_]+ ([0-9] | [a-zA-Z_])*

WHITESPACE [ \t\n\r]

%option noyywrap
%option yylineno
%option warn nodefault
%option c++

%%
 
        // Warning: Use double quotes for literals!

"/"       { fyylval.stdstring = "/"; return tdiv; }
"{"       { fyylval.stdstring = "{";  return tbracket_curly_open;  }
"}"       { fyylval.stdstring = "}";  return tbracket_curly_close; }
"["       { fyylval.stdstring = "[";  return tbracket_square_open; }
"]"       { fyylval.stdstring = "]";  return tbracket_square_close; }
"scene"       { fyylval.stdstring = "scene";  return tscene; }
"choice"        { fyylval.stdstring = "choice";  return tchoice; }
"goto"        { fyylval.stdstring = "goto";  return tgoto; }
[A-Za-z_]+([a-za-z0-9_])*       { fyylval.stdstring = yytext;  return tidentifier; }
(\"([^\"\\]|(\\[a-za-z\"]))*\")|(\'([^\'\\]|(\\[a-za-z\']))*\')  { fyylval.stdstring = yytext;  return tstring; }
<<EOF>>       {  return 0; }
"\r\n"      { ++flexLineNo; }
"\r"      { ++flexLineNo; }
"\n"      { ++flexLineNo; }
[ \t]          /* Ignore */
"."     { fyylval.stdstring = ".";  return tfullstop; }
.       { printf("Lexing error on line %d: \"%s\"\n", yylineno, yytext); }
%%
