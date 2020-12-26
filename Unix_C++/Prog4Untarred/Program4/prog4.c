/*
  Filename  prog4.c
  Date      3/28/19
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    C program containing main routine for scanning and parsing an input file.
*/

#include "header.h"
#include "y.tab.h"

extern char* yytext;
int yylex(void);
int yyparse(void);

int main(int argc, char *argv[])
{
  if(strcmp(argv[0],"./scanner") == 0)
  {
    printf("Operating in scanner mode\n");
    int sresult = yylex();
    while(sresult != 0)
    {
      printf("yylex returned ");
      switch(sresult)
      {
        case SRTOKEN: printf("SRTOKEN token (%d)\n", sresult);
	        break;
        case JRTOKEN: printf("JRTOKEN token (%d)\n", sresult);
	        break;
        case EOLTOKEN: printf("EOLTOKEN token (%d)\n", sresult);
	        break;
        case COMMATOKEN: printf("COMMATOKEN token (%d)\n", sresult);
	        break;
        case DASHTOKEN: printf("DASHTOKEN token (%d)\n", sresult);
	        break;
        case HASHTOKEN: printf("HASHTOKEN token (%d)\n", sresult);
	        break;
        case INTTOKEN: printf("INTTOKEN token (%d)\n", atoi(yytext));
	        break;
        case ROMANTOKEN: printf("ROMANTOKEN token (%s)\n", yytext);
	        break;
        case NAME_INITIAL_TOKEN: printf("NAME_INITIAL_TOKEN token (%s)\n", yytext);
                break;
        case NAMETOKEN: printf("NAMETOKEN token (%s)\n", yytext);
	         break;
        case IDENTIFIERTOKEN: printf("IDENTIFIERTOKEN token (%s)\n", yytext);
	         break;
        default: printf("error\n");
	         break;
      }
      sresult = yylex();
    }
  }
  else if(strcmp(argv[0],"./parser") == 0)
  {
    printf("Operating in parser mode\n");
    switch(yyparse())
    {
      case 0: printf("\nParse complete!\n");
      break;
      case 1: printf("\nParse failed!\n");
      break;
      case 2: printf("\nOut of Memory\n");
      break;
      default: printf("Unkown result from yyparse()\n");
      break;
    }
  }
  else
    printf("Call this executable with the name scanner or parser\n");
  return 0;
}
