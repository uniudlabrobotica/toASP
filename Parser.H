#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include<vector>
#include<string>


class Program;
class Decl;
class Predicate;
class Literal;
class Action;
class ListLiteral;
class ListIdent;
class ListDecl;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Program* program_;
  Decl* decl_;
  Predicate* predicate_;
  Literal* literal_;
  Action* action_;
  ListLiteral* listliteral_;
  ListIdent* listident_;
  ListDecl* listdecl_;
} YYSTYPE;

Program* pProgram(FILE *inp);
Program* pProgram(const char *str);



#define _ERROR_ 258
#define _SYMB_0 259
#define _SYMB_1 260
#define _SYMB_2 261
#define _SYMB_3 262
#define _SYMB_4 263
#define _SYMB_5 264
#define _SYMB_6 265
#define _SYMB_7 266
#define _SYMB_8 267
#define _SYMB_9 268
#define _SYMB_10 269
#define _SYMB_11 270
#define _IDENT_ 271

extern YYSTYPE yylval;

#endif
