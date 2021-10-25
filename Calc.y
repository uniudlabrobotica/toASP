/* This Bison file was machine-generated by BNFC */
%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Absyn.H"
typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yyparse(void);
int yylex(void);
YY_BUFFER_STATE yy_scan_string(const char *str);
void yy_delete_buffer(YY_BUFFER_STATE buf);
int yy_mylinenumber;
int initialize_lexer(FILE * inp);
int yywrap(void)
{
  return 1;
}
void yyerror(const char *str)
{
  extern char *yytext;
  fprintf(stderr,"error: line %d: %s at %s\n", 
    yy_mylinenumber, str, yytext);
}



static Program* YY_RESULT_Program_ = 0;
Program* pProgram(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}
Program* pProgram(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}

static Decl* YY_RESULT_Decl_ = 0;
Decl* pDecl(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Decl_;
  }
}
Decl* pDecl(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Decl_;
  }
}

static Predicate* YY_RESULT_Predicate_ = 0;
Predicate* pPredicate(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Predicate_;
  }
}
Predicate* pPredicate(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Predicate_;
  }
}

static Literal* YY_RESULT_Literal_ = 0;
Literal* pLiteral(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Literal_;
  }
}
Literal* pLiteral(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Literal_;
  }
}

static Action* YY_RESULT_Action_ = 0;
Action* pAction(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Action_;
  }
}
Action* pAction(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Action_;
  }
}

static ListLiteral* YY_RESULT_ListLiteral_ = 0;
ListLiteral* pListLiteral(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListLiteral_;
  }
}
ListLiteral* pListLiteral(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListLiteral_;
  }
}

static ListIdent* YY_RESULT_ListIdent_ = 0;
ListIdent* pListIdent(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListIdent_;
  }
}
ListIdent* pListIdent(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListIdent_;
  }
}

static ListDecl* YY_RESULT_ListDecl_ = 0;
ListDecl* pListDecl(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListDecl_;
  }
}
ListDecl* pListDecl(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListDecl_;
  }
}



%}

%union
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
}

%token _ERROR_
%token _SYMB_0    //   (
%token _SYMB_1    //   )
%token _SYMB_2    //   ,
%token _SYMB_3    //   .
%token _SYMB_4    //   causes
%token _SYMB_5    //   executable
%token _SYMB_6    //   finally
%token _SYMB_7    //   if
%token _SYMB_8    //   initially
%token _SYMB_9    //   neg
%token _SYMB_10    //   of
%token _SYMB_11    //   type

%type <program_> Program
%type <decl_> Decl
%type <predicate_> Predicate
%type <literal_> Literal
%type <action_> Action
%type <listliteral_> ListLiteral
%type <listident_> ListIdent
%type <listdecl_> ListDecl

%start Program
%token<string_> _IDENT_

%%
Program : ListDecl {  std::reverse($1->begin(),$1->end()) ;$$ = new Prg($1); YY_RESULT_Program_= $$; } 
;
Decl : _IDENT_ _SYMB_10 _SYMB_11 _IDENT_ {  $$ = new Def($1, $4);  } 
  | _SYMB_5 Action _SYMB_7 ListLiteral {  std::reverse($4->begin(),$4->end()) ;$$ = new Exec($2, $4);  }
  | Action _SYMB_4 ListLiteral {  std::reverse($3->begin(),$3->end()) ;$$ = new Caus($1, $3);  }
  | Action _SYMB_4 ListLiteral _SYMB_7 ListLiteral {  std::reverse($3->begin(),$3->end()) ; std::reverse($5->begin(),$5->end()) ;$$ = new CausCond($1, $3, $5);  }
  | _SYMB_8 Literal {  $$ = new Init($2);  }
  | _SYMB_6 Literal {  $$ = new Final($2);  }
;
Predicate : _IDENT_ _SYMB_0 ListIdent _SYMB_1 {  std::reverse($3->begin(),$3->end()) ;$$ = new Preds($1, $3);  } 
  | _IDENT_ {  $$ = new Pred($1);  }
;
Literal : _SYMB_9 Predicate {  $$ = new LitN($2);  } 
  | Predicate {  $$ = new Lit($1);  }
;
Action : _IDENT_ _SYMB_0 ListIdent _SYMB_1 {  std::reverse($3->begin(),$3->end()) ;$$ = new Acts($1, $3);  } 
  | _IDENT_ {  $$ = new Act($1);  }
;
ListLiteral : Literal {  $$ = new ListLiteral() ; $$->push_back($1);  } 
  | Literal _SYMB_2 ListLiteral {  $3->push_back($1) ; $$ = $3 ;  }
;
ListIdent : _IDENT_ {  $$ = new ListIdent() ; $$->push_back($1);  } 
  | _IDENT_ _SYMB_2 ListIdent {  $3->push_back($1) ; $$ = $3 ;  }
;
ListDecl : Decl _SYMB_3 {  $$ = new ListDecl() ; $$->push_back($1);  } 
  | Decl _SYMB_3 ListDecl {  $3->push_back($1) ; $$ = $3 ;  }
;

