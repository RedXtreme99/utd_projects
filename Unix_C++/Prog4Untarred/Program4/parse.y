 /* Filename  parse.y                   */
 /* Date      3/28/19                   */
 /* Author    Basil Elhindi             */
 /* Email     bae170000@utdallas.edu    */
 /* Course    CS 3377.502 Spring 2019   */
 /* Version   1.0                       */
 /* Copyright 2019, All Rights Reserved */
 /*                                     */
 /* Description                         */
 /*   Bison file meant to parse input   */
 /*   file and generate XML output.     */

%{
  #include "header.h"
  #include "y.tab.h"
  char *str;
  int value;
  void yyerror(char *s); 
%}

%union {
  char *str;
  int num;
}

%type <str> SRTOKEN
%type <str> JRTOKEN
%type <str> EOLTOKEN
%type <str> COMMATOKEN
%type <str> DASHTOKEN
%type <str> HASHTOKEN
%type <num> INTTOKEN
%type <str> ROMANTOKEN
%type <str> NAME_INITIAL_TOKEN
%type <str> NAMETOKEN
%type <str> IDENTIFIERTOKEN

%token SRTOKEN
%token JRTOKEN
%token EOLTOKEN
%token COMMATOKEN
%token DASHTOKEN
%token HASHTOKEN
%token INTTOKEN
%token ROMANTOKEN
%token NAME_INITIAL_TOKEN
%token NAMETOKEN
%token IDENTIFIERTOKEN

%start postaladdresses

%%

postaladdresses: addressblock EOLTOKEN postaladdresses
               | addressblock 
               ;

addressblock: namepart streetaddress locationpart { fprintf(stderr, "\n"); }
            ;

namepart: personalpart lastname suffixpart EOLTOKEN
        | personalpart lastname EOLTOKEN
        | error EOLTOKEN
        ;

personalpart: NAMETOKEN { fprintf(stderr, "<FirstName>%s</FirstName>\n", $1); }
            | NAME_INITIAL_TOKEN { fprintf(stderr, "<FirstName>%s</FirstName>\n", $1); }
            ;

lastname: NAMETOKEN { fprintf(stderr, "<LastName>%s</LastName>\n", $1); }
        ;

suffixpart: SRTOKEN { fprintf(stderr, "<Suffix>%s</Suffix>\n", $1); }
          | JRTOKEN { fprintf(stderr, "<Suffix>%s</Suffix>\n", $1); }
          | ROMANTOKEN { fprintf(stderr, "<Suffix>%s</Suffix>\n", $1); }
          ;

streetaddress: streetnumber streetname aptnumber EOLTOKEN
             | streetnumber streetname HASHTOKEN aptnumber EOLTOKEN
             | streetnumber streetname EOLTOKEN
             | error EOLTOKEN
             ;

streetnumber: INTTOKEN { fprintf(stderr, "<HouseNumber>%d</HouseNumber>\n", $1); }
            | IDENTIFIERTOKEN {fprintf(stderr, "<HouseNumber>%s</HouseNumber>\n", $1); }
            ;

streetname: NAMETOKEN { fprintf(stderr, "<StreetName>%s</StreetName>\n", $1); }
          ;

aptnumber: INTTOKEN { fprintf(stderr, "<AptNum>%d</AptNum>\n", $1); }

locationpart: townname COMMATOKEN statecode zipcode EOLTOKEN
            | error EOLTOKEN
            ;

townname: NAMETOKEN { fprintf(stderr, "<City>%s</City>\n", $1); }
        ;

statecode: NAMETOKEN { fprintf(stderr, "<State>%s</State>\n", $1); }
         ;

zipcode: zipfive DASHTOKEN zipfour
       | zipfive
       ;

zipfive: INTTOKEN { fprintf(stderr, "<Zip5>%d</Zip5>\n", $1); }
       ;

zipfour: INTTOKEN { fprintf(stderr, "<Zip4>%d</Zip4>\n", $1); }
       ;
 
%%

void yyerror(char *s)
{
  printf("Bad %s ... skipping to newline\n", s);
}
