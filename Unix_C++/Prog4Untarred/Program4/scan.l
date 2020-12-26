 /* Filename  scan.l	                */
 /* Date      3/28/2019                 */
 /* Author    Basil Elhindi             */
 /* Email     bae170000@utdallas.edu    */
 /* Course    CS 3377.502 Spring 2019   */
 /* Version   1.0                       */
 /* Copyright 2019, All Rights Reserved */
 /* Description                         */
 /*  Lex file to scan input file and    */
 /*  create tokens that can be used     */
 /*  alongside a parser.                */
 
%option noyywrap
%option nounput
%option noinput

%{
#include "y.tab.h"
#include "header.h"
%}

%%

[ \t\r]+
"Sr."		  { yylval.str = "Sr."; return SRTOKEN; }
"Jr."		  { yylval.str = "Jr."; return JRTOKEN;}
"\n"		  { yylval.str = "\n"; return EOLTOKEN; }
","		  { yylval.str = ","; return COMMATOKEN; }
"-"		  { yylval.str = "-"; return DASHTOKEN; }
"#"		  { yylval.str = "#"; return HASHTOKEN; }
[0-9]+		  { yylval.num = atoi(yytext); return INTTOKEN; }
[IV]+		  { yylval.str = strdup(yytext); return ROMANTOKEN; }
[a-zA-Z]\.?	  { yylval.str = strdup(yytext); return NAME_INITIAL_TOKEN; }
[a-zA-Z][a-zA-Z]+ { yylval.str = strdup(yytext); return NAMETOKEN; }
[a-zA-Z0-9]+ 	  { yylval.str = strdup(yytext); return IDENTIFIERTOKEN; }

%%

