/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2




FluentVisitor::FluentVisitor(void)
{

  myfile.open ("toAsp.lp", std::ios::app);

}

FluentVisitor::~FluentVisitor(void)
{
  myfile.close();
}

void FluentVisitor::print(Visitable *v)
{

  v->accept(this);
  return ;
}
void FluentVisitor::visitProgram(Program*p) {} //abstract class

void FluentVisitor::visitPrg(Prg* p)
{

  if(p->listdecl_) {int _i_ = 0; p->listdecl_->accept(this);}
 
}
void FluentVisitor::visitAction(Action *p){} //abstract class

void FluentVisitor::visitActs(Acts* p)
{
  myfile<<"action("<<p->ident_<<"(";
  for (ListIdent::const_iterator i = p->listident_->begin() ; i != p->listident_->end() ; ++i)
  {
    myfile << *i;
    /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
    if (i != p->listident_->end() - 1) myfile << ", " ;
  }
  myfile << ")):-";
  for (ListIdent::const_iterator i = p->listident_->begin() ; i != p->listident_->end() ; ++i)
  {
    myfile << "blocco("<<*i<<")";
    /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
    if (i != p->listident_->end() - 1) myfile << ", " ;
  }
  myfile << ".\n";
  
}

void FluentVisitor::visitAct(Act* p)
{
  myfile<<"action("<<p->ident_<<").";
}

void FluentVisitor::visitDecl(Decl*p) {} //abstract class

void FluentVisitor::visitExec(Exec* p)
{
  p->action_->accept(this);
  if(p->listliteral_) {int _i_ = 0; p->listliteral_->accept(this);}

}

void FluentVisitor::visitCaus(Caus* p)
{
  p->action_->accept(this);
  if(p->listliteral_) {int _i_ = 0; p->listliteral_->accept(this);}
}

void FluentVisitor::visitCausCond(CausCond* p)
{
  p->action_->accept(this);
  if(p->listliteral_1) {int _i_ = 0; p->listliteral_1->accept(this);}
  if(p->listliteral_2) {int _i_ = 0; p->listliteral_2->accept(this);}
}


void FluentVisitor::visitPredicate(Predicate*p) {} //abstract class

void FluentVisitor::visitLitN(LitN* p)
{
  int _i_ = 0; p->predicate_->accept(this);

}

void FluentVisitor::visitPreds(Preds* p)
{

  myfile << "fluent("<<p->ident_<<"(";
  if(p->listident_) {int _i_ = 0; p->listident_->accept(this);}  
  
  myfile << ")):-";
  for (ListIdent::const_iterator i = p->listident_->begin() ; i != p->listident_->end() ; ++i)
  {
    myfile<<"blocco("<<(*i)<<")";
    if (i != p->listident_->end() - 1) myfile<<", ";
  }
  myfile << ".\n";
  
}

void FluentVisitor::visitPred(Pred* p)
{
  
  //visitIdent(p->ident_);
  myfile << "fluent("<<p->ident_<<").\n";

}

void FluentVisitor::visitLiteral(Literal*p) {} //abstract class


void FluentVisitor::visitLit(Lit* p)
{
  int _i_ = 0; p->predicate_->accept(this);

}


void FluentVisitor::visitListLiteral(ListLiteral *listliteral)
{
  for (ListLiteral::const_iterator i = listliteral->begin() ; i != listliteral->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listliteral->end() - 1) ;
  }
}void FluentVisitor::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    myfile << *i;
    /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
    if (i != listident->end() - 1) myfile << ", " ;
  }
}
void FluentVisitor::visitListDecl(ListDecl *listdecl)
{
  for (ListDecl::const_iterator i = listdecl->begin() ; i != listdecl->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdecl->end() - 1) ;
  }
}
void FluentVisitor::visitIdent(String s)
{
  //myfile << "fluent("<<s<<").\n";
}

/*
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
*/


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char* s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();


}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
void PrintAbsyn::visitProgram(Program*p) {} //abstract class

void PrintAbsyn::visitPrg(Prg* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listdecl_) {_i_ = 0; p->listdecl_->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDecl(Decl*p) {} //abstract class

void PrintAbsyn::visitExec(Exec* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("executable");
  _i_ = 0; p->action_->accept(this);
  render("if");
  if(p->listliteral_) {_i_ = 0; p->listliteral_->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCaus(Caus* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->action_->accept(this);
  render("causes");
  if(p->listliteral_) {_i_ = 0; p->listliteral_->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCausCond(CausCond* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->action_->accept(this);
  render("causes");
  if(p->listliteral_1) {_i_ = 0; p->listliteral_1->accept(this);}  render("if");
  if(p->listliteral_2) {_i_ = 0; p->listliteral_2->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInit(Init* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("initially");
  _i_ = 0; p->literal_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredicate(Predicate*p) {} //abstract class

void PrintAbsyn::visitPreds(Preds* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}  render(')');
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPred(Pred* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);
  
  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLiteral(Literal*p) {} //abstract class

void PrintAbsyn::visitLitN(LitN* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("neg");
  _i_ = 0; p->predicate_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLit(Lit* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->predicate_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitAction(Action*p) {} //abstract class

void PrintAbsyn::visitActs(Acts* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}  render(')');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitAct(Act* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListLiteral(ListLiteral *listliteral)
{
  for (ListLiteral::const_iterator i = listliteral->begin() ; i != listliteral->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listliteral->end() - 1) render(',');
  }
}void PrintAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
    if (i != listident->end() - 1) render(',');
  }
}void PrintAbsyn::visitListDecl(ListDecl *listdecl)
{
  for (ListDecl::const_iterator i = listdecl->begin() ; i != listdecl->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdecl->end() - 1) render('.');
  }
}void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
void ShowAbsyn::visitProgram(Program* p) {} //abstract class

void ShowAbsyn::visitPrg(Prg* p)
{
  bufAppend('(');
  bufAppend("Prg");
  bufAppend(' ');
  bufAppend('[');
  if (p->listdecl_)  p->listdecl_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDecl(Decl* p) {} //abstract class

void ShowAbsyn::visitExec(Exec* p)
{
  bufAppend('(');
  bufAppend("Exec");
  bufAppend(' ');
  bufAppend('[');
  if (p->action_)  p->action_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listliteral_)  p->listliteral_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCaus(Caus* p)
{
  bufAppend('(');
  bufAppend("Caus");
  bufAppend(' ');
  bufAppend('[');
  if (p->action_)  p->action_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listliteral_)  p->listliteral_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCausCond(CausCond* p)
{
  bufAppend('(');
  bufAppend("CausCond");
  bufAppend(' ');
  bufAppend('[');
  if (p->action_)  p->action_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->listliteral_1->accept(this);
  bufAppend(' ');
  p->listliteral_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitInit(Init* p)
{
  bufAppend('(');
  bufAppend("Init");
  bufAppend(' ');
  bufAppend('[');
  if (p->literal_)  p->literal_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredicate(Predicate* p) {} //abstract class

void ShowAbsyn::visitPreds(Preds* p)
{
  bufAppend('(');
  bufAppend("Preds");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitPred(Pred* p)
{
  bufAppend('(');
  bufAppend("Pred");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitLiteral(Literal* p) {} //abstract class

void ShowAbsyn::visitLitN(LitN* p)
{
  bufAppend('(');
  bufAppend("LitN");
  bufAppend(' ');
  bufAppend('[');
  if (p->predicate_)  p->predicate_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitLit(Lit* p)
{
  bufAppend('(');
  bufAppend("Lit");
  bufAppend(' ');
  bufAppend('[');
  if (p->predicate_)  p->predicate_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitAction(Action* p) {} //abstract class

void ShowAbsyn::visitActs(Acts* p)
{
  bufAppend('(');
  bufAppend("Acts");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitAct(Act* p)
{
  bufAppend('(');
  bufAppend("Act");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitListLiteral(ListLiteral *listliteral)
{
  for (ListLiteral::const_iterator i = listliteral->begin() ; i != listliteral->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listliteral->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListDecl(ListDecl *listdecl)
{
  for (ListDecl::const_iterator i = listdecl->begin() ; i != listdecl->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdecl->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}


