#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <regex>
#include <map>



/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'


class FluentVisitor : public Visitor
{
 private:
  std::ofstream myfile;
  static std::map<std::string, std::string> vars_predicates;

 public:

  FluentVisitor(void);
  ~FluentVisitor(void);
  void print(Visitable* v);
  void visitProgram(Program *p); /* abstract class */
  void visitPrg(Prg *p);
  void visitDecl(Decl *p); /* abstract class */
  void visitExec(Exec *p);
  void visitCaus(Caus *p);
  void visitDef(Def *p);
  void visitCausCond(CausCond *p);
  void visitPredicate(Predicate *p); /* abstract class */
  void visitPreds(Preds *p);
  void visitPred(Pred *p);
  void visitLiteral(Literal *p); /* abstract class */
  void visitLitN(LitN *p);
  void visitLit(Lit *p);
  void visitListLiteral(ListLiteral* p);
  void visitListDecl(ListDecl* p);
  void visitListIdent(ListIdent* p);
  void visitIdent(String s);
  void visitInteger(Integer){};
  void visitAction(Action *p); /* abstract class */
  void visitActs(Acts *p);
  void visitAct(Act *p);
  void visitFinal(Final *p);
  void visitInit(Init *p);
  void visitChar(Char x){};
  void visitDouble(Double x){};
  void visitString(String x){};
};

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
void render(char* s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char* print(Visitable* v);

  void visitProgram(Program *p); /* abstract class */
  void visitPrg(Prg *p);
  void visitDecl(Decl *p); /* abstract class */
  void visitDef(Def *p);
  void visitExec(Exec *p);
  void visitCaus(Caus *p);
  void visitCausCond(CausCond *p);
  void visitInit(Init *p);
  void visitFinal(Final *p);
  void visitPredicate(Predicate *p); /* abstract class */
  void visitPreds(Preds *p);
  void visitPred(Pred *p);
  void visitLiteral(Literal *p); /* abstract class */
  void visitLitN(LitN *p);
  void visitLit(Lit *p);
  void visitAction(Action *p); /* abstract class */
  void visitActs(Acts *p);
  void visitAct(Act *p);
  void visitListLiteral(ListLiteral* p);
  void visitListIdent(ListIdent* p);
  void visitListDecl(ListDecl* p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char* show(Visitable* v);

  void visitProgram(Program *p); /* abstract class */
  void visitPrg(Prg *p);
  void visitDecl(Decl *p); /* abstract class */
  void visitDef(Def *p);
  void visitExec(Exec *p);
  void visitCaus(Caus *p);
  void visitCausCond(CausCond *p);
  void visitInit(Init *p);
  void visitFinal(Final *p);
  void visitPredicate(Predicate *p); /* abstract class */
  void visitPreds(Preds *p);
  void visitPred(Pred *p);
  void visitLiteral(Literal *p); /* abstract class */
  void visitLitN(LitN *p);
  void visitLit(Lit *p);
  void visitAction(Action *p); /* abstract class */
  void visitActs(Acts *p);
  void visitAct(Act *p);
  void visitListLiteral(ListLiteral* p);
  void visitListIdent(ListIdent* p);
  void visitListDecl(ListDecl* p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};




#endif

