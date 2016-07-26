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
 #include "Grammar.tab.hpp"

 int flexLineNo=1;
%}

IDENTIFIER [a-zA-Z_]+ ([0-9] | [a-zA-Z_])*

WHITESPACE [ \t\n\r]

%option noyywrap
%option yylineno
%option warn nodefault
%option c++

%%
 
        // Warning: Use double quotes for literals!

"/"       { fyylval.charstrval = "/"; return tdiv; }
"{"       { fyylval.charstrval = "{";  return tbracket_curly_open;  }
"}"       { fyylval.charstrval = "}";  return tbracket_curly_close; }
"["       { fyylval.charstrval = "[";  return tbracket_square_open; }
"]"       { fyylval.charstrval = "]";  return tbracket_square_close; }
"scene"       { fyylval.charstrval = "scene";  return tscene; }
"choice"        { fyylval.charstrval = "choice";  return tchoice; }
"goto"        { fyylval.charstrval = "goto";  return tgoto; }
[A-Za-z_]+([a-za-z0-9_])*       { fyylval.stringval = new std::string(yytext);  return tidentifier; }
(\"([^\"\\]|(\\[a-za-z\"]))*\")|(\'([^\'\\]|(\\[a-za-z\']))*\')  { fyylval.stringval = new std::string(yytext);  return tstring; }
<<EOF>>       {  return 0; }
"\r\n"      { ++flexLineNo; }
"\r"      { ++flexLineNo; }
"\n"      { ++flexLineNo; }
[ \t]          /* Ignore */
"."     { fyylval.charstrval = ".";  return tfullstop; }
.       { printf("Lexing error on line %d: \"%s\"\n", yylineno, yytext); }
%%