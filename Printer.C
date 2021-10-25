/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2

std::string getBodyLiteral(std::string &s, std::string &ident, std::map<std::string, std::string> &m){
    std::regex regex{R"([\s+\-]+)"}; // split on + and -
    std::sregex_token_iterator it{ident.begin(), ident.end(), regex, -1};
    std::vector<std::string> words{it, {}};

    std::vector<std::string> noNumbers;
    std::copy_if (words.begin(), words.end(), std::back_inserter(noNumbers), [](std::string t){return !std::any_of(t.begin(), t.end(), ::isdigit);} );
    int count = 0;
    int len = noNumbers.size();
    for(std::string t : noNumbers){
      s = s + m[t]+"("+t+")";
      if (count != len-1) s = s + ",";
      count++; 
    }

    return s;
}

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

  if(p->listdecl_) {p->listdecl_->accept(this);}
  int l = 10;

  myfile << "time(1.." << l << ").\n";

  myfile << "h(1..3).\n";
  myfile << "block(a;b;c;d).\n";
  myfile << "place(1..3).\n";
  myfile << "not_ok(T) :- time(T), finally(F), not holds(F,T).\n";
  //myfile << "goal(T) :- fluent(F), time(T), not holds(F,T).\n";
  myfile << "goal(T) :- time(T), not not_ok(T).\n";
  myfile << ":- not goal("<<l<<").\n";

  myfile << "opposto(F,neg(F)):- fluent(F).\n";
  myfile << "opposto(neg(F),F):- fluent(F).\n";

  myfile << "not_executable(A,T):- time(T), exec(A,F), not holds(F,T).\n";
  myfile << "executable(A,T):- action(A), time(T), T<"<< l<<", not not_executable(A,T).\n";
  myfile << "holds(F,T+1):- T<"<< l <<", executable(A,T), occurs(A,T), causes(A,F).\n";
  myfile << "holds(F,T+1):- T<"<< l <<", executable(A,T), occurs(A,T), causes(A,F,T).\n"; // NEW ENTRY!!!!


  myfile << "holds(F,T+1):-opposto(F,G), T<"<<l<<", holds(F,T), not holds(G,T+1).\n";

  myfile << "occurs(A,T):- action(A), time(T), not goal(T), not not_occurs(A,T).\n";
  myfile << "not_occurs(A,T):- action(A), action(B), time(T), occurs(B,T), A!=B.\n";
  myfile << ":- action(A), time(T), occurs(A,T), not executable(A,T).\n";

  myfile << "action(noop).\n";

  myfile << "holds(F,1):-initially(F).\n";

  myfile << "holds(F):- holds(F,"<<l<<").\n";

  myfile << "#maximize { T:occurs(noop,T) }.\n";
  myfile << "#show occurs/2.\n";
  //myfile << "#show holds/1.\n";


}
void FluentVisitor::visitAction(Action *p){} //abstract class

std::string getVarsfromListIdent(std::string str, ListIdent* listident, std::map<Ident,Ident> &vars_predicates){
  std::string vars = "";
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i){
    std::string s = "";
    std::string j = (std::string) *i;
    vars = vars + getBodyLiteral(s, j, vars_predicates);
    /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
    if (i != listident->end() - 1) vars = vars + ", " ;
  }
  return vars;
}


std::string getVarsfromAction(std::string str, Action* act, std::map<Ident,Ident> &vars_predicates){
  std::string vars = "";
  std::string typeOfAction = typeid(*act).name();
  if(typeOfAction.find("4") != std::string::npos){
    Acts* a = (Acts*) act;

    ListIdent* listident = a->listident_;
    for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i){
      std::string s = "";
      std::string j = (std::string) *i;
      vars = vars + getBodyLiteral(s, j, vars_predicates);
      /*std::cout<<"\n" << *i << "\n";//QUA stampa ident*/
      if (i != listident->end() - 1) vars = vars + ", " ;
    }

  }
  return vars;
}

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
  std::string str = "";
  myfile << getVarsfromAction(str, (Action*)p, FluentVisitor::vars_predicates)<< ".\n";
}

void FluentVisitor::visitAct(Act* p)
{
  myfile<<"action("<<p->ident_<<").";
}

void FluentVisitor::visitDecl(Decl*p) {} //abstract class

std::string action2str(std::string str, Action* act){
  if(typeid(*act).name()=="4Act"){
    Act* a = (Act*) act;
    str = a->ident_;
  }else{
    Acts* a = (Acts*) act;
    str = a->ident_ + "(";
    ListIdent* listident = a->listident_;
    for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i){
      str = str + *i;
      if (i != listident->end() - 1) str = str + ", " ;
    }
    str = str + "), ";
  }
  return str;
}

std::string listIdent2str(std::string lstident2str, ListIdent *listident)
{
  lstident2str = "";
  int numidents = listident->size();
  int counteridents = 0;
  for (auto& j : *listident){
      lstident2str = lstident2str + j;
      if (counteridents != numidents-1) lstident2str = lstident2str + ", ";
      counteridents++;
  }
  return lstident2str;
}

std::string literal2str(std::string lit2str, Literal *literal){

  lit2str = "";
  std::string typeLiteral = typeid(*literal).name();
  bool negated = typeLiteral.find('N') != std::string::npos;

  Predicate *predicate;
  if (!negated){

    Lit* l = (Lit*) literal;
    predicate=l->predicate_;

  }else {

    LitN* l = (LitN*) literal;
    predicate=l->predicate_;
    lit2str = lit2str + "neg(";

  }
  std::string typePredicate = typeid(*predicate).name();
  if (typePredicate.find('s') != std::string::npos){
    Preds* p = (Preds*) predicate;
    lit2str = lit2str + p->ident_;
    ListIdent* listident = p->listident_;
    std::string lstident2str = "";
    lit2str += "(" + listIdent2str(lstident2str, listident) + ")";
  }else {
    Pred* p = (Pred*) predicate;
    lit2str = lit2str + p->ident_;
  }
  if (negated) lit2str = lit2str+ ")";

  return lit2str;
}

std::string getVarsFromLiteral(std::string litVars2str, Literal *literal, std::map<std::string, std::string> &vars_predicates){

  litVars2str = "";
  std::string typeLiteral = typeid(*literal).name();
  bool negated = typeLiteral.find('N') != std::string::npos;

  Predicate *predicate;
  if (!negated){

    Lit* l = (Lit*) literal;
    predicate=l->predicate_;

  }else {

    LitN* l = (LitN*) literal;
    predicate=l->predicate_;
  }
  std::string typePredicate = typeid(*predicate).name();
  if (typePredicate.find('s') != std::string::npos){
    Preds* p = (Preds*) predicate;
    ListIdent* listident = p->listident_;
    std::string listidentstr = "";
    litVars2str = getVarsfromListIdent(listidentstr, listident, vars_predicates);
  }else {
    Pred* p = (Pred*) predicate;
  }

  return litVars2str;
}


std::string listLiteral2str_2(std::string lstlit2str, ListLiteral *listliteral, std::string type, Action *action, std::map<std::string,std::string> &vars_predicates)
{
  for (auto& i : *listliteral){
    std::string lit2str = "";
    std::string act2str = "";
    std::string actIdents2str = "";
    std::string varsFromLit = "";
    lit2str=literal2str(lit2str, i);
    actIdents2str = getVarsfromAction(actIdents2str, action, vars_predicates);
    varsFromLit= getVarsFromLiteral(varsFromLit, i, vars_predicates);
    if (actIdents2str.size()>0 & varsFromLit.size() > 0)
      actIdents2str = actIdents2str + ", ";
    std::string implicazione = "";
    if (actIdents2str.size()>0 | varsFromLit.size() > 0)
      implicazione = ":-";
    lstlit2str=lstlit2str+type+"("+action2str(act2str, action)+lit2str+")"+implicazione+ actIdents2str + getVarsFromLiteral(varsFromLit, i, vars_predicates)+".\n";
  }
  return lstlit2str;
}

std::string fromLiteralList2HoldsList(std::string res, ListLiteral *listliteral){

  int count = 0;
  int len = listliteral->size();
  for (auto& literal : *listliteral){
    std::string lit2str = "";
    lit2str = literal2str(lit2str, literal);
    res = res + "holds("+lit2str+",T)";
    if(len-1 != count) res = res + ", "; 
    count++;
  }
  return res;
}

std::string getVarsfromListLiteral(std::string& res, ListLiteral* l, std::map<std::string, std::string> map){

    res = "";
    int len = l->size();
    int count = 0;
    for (auto& literal : *l){
    
      std::string lit2str = "";
      lit2str=getVarsFromLiteral(lit2str, literal, map);
      res = res + lit2str;

      if (len-1 != count) res = res + ",";

  }
  return res;

}

std::string causCond2str(std::string result, ListLiteral *literals2Modify, ListLiteral *ifLiterals, Action *action, std::map<std::string,std::string> &map){
  std::string act2str = "";
  act2str = action2str(act2str, action);

  std::string actVars = "";
  actVars = getVarsfromAction(actVars, action, map);

  std::string hold = "";
  hold=fromLiteralList2HoldsList(hold, ifLiterals);
    
  std::string varsFromListLiteral = "";    
  varsFromListLiteral= getVarsfromListLiteral(varsFromListLiteral, ifLiterals, map);

  for (auto& literal : *literals2Modify){
    
    std::string lit2str = "";
    lit2str=literal2str(lit2str, literal);

    std::string varsFromLit = "";    
    varsFromLit= getVarsFromLiteral(varsFromLit, literal, map);

    std::string separator0 = (actVars.size()>0 | varsFromLit.size() > 0 | hold.size() > 0 | varsFromListLiteral.size() > 0) ? ", " : "";
    std::string separator1 = (actVars.size()>0 & (varsFromLit.size() > 0 | hold.size() > 0 | varsFromListLiteral.size() > 0)) ? ", " : "";
    std::string separator2 = (varsFromLit.size()>0 & (hold.size() > 0 | varsFromListLiteral.size() > 0)) ? ", " : "";
    std::string separator3 = (hold.size()>0 & varsFromListLiteral.size() > 0) ? ", " : "";

    result=result+"causes("+act2str+lit2str+", T):-time(T)"+ separator0 + actVars + separator1 + varsFromLit + separator2 + hold + separator3 + varsFromListLiteral + ".\n";

  }
  return result;
}




void FluentVisitor::visitExec(Exec* p)
{
  p->action_->accept(this);
  if(p->listliteral_) {p->listliteral_->accept(this);}
  Action* act = p->action_;
  std::string type= "exec";
  std::string lstlit2str = "";
  myfile << listLiteral2str_2(lstlit2str, p->listliteral_, type, act, FluentVisitor::vars_predicates);
}


void FluentVisitor::visitCaus(Caus* p)
{
  p->action_->accept(this);
  if(p->listliteral_) {int _i_ = 0; p->listliteral_->accept(this);}
  Action* act = p->action_;
  std::string type= "causes";
  std::string lstlit2str = "";
  myfile << listLiteral2str_2(lstlit2str, p->listliteral_, type, act, FluentVisitor::vars_predicates);
}

void FluentVisitor::visitCausCond(CausCond* p)
{
  p->action_->accept(this);
  if(p->listliteral_1) {int _i_ = 0; p->listliteral_1->accept(this);}
  if(p->listliteral_2) {int _i_ = 0; p->listliteral_2->accept(this);}
  Action* act = p->action_;
  std::string type = "causes";
  std::string act2str = "";
  myfile << causCond2str(act2str, p->listliteral_1, p->listliteral_2, act, FluentVisitor::vars_predicates);
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
    std::string s = "";
    std::string j = (std::string) *i;
    myfile << getBodyLiteral(s, j, FluentVisitor::vars_predicates);
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

void FluentVisitor::visitInit(Init* p)
{

  myfile << "initially(";
  std::string lstlit2str = "";
  Literal* literal = p->literal_;
  myfile << literal2str(lstlit2str, literal);
  myfile << ").\n";
}

void FluentVisitor::visitFinal(Final* p)
{
  myfile << "finally(";
  std::string lstlit2str = "";
  Literal* literal = p->literal_;
  myfile << literal2str(lstlit2str, literal);
  myfile << ").\n";

}

void FluentVisitor::visitDef(Def* p)
{
  std::string id = (p->ident_1);
  std::string id2 = (p->ident_2);
  FluentVisitor::vars_predicates.insert(std::make_pair(id, id2));
}

std::map<std::string, std::string> FluentVisitor::vars_predicates;

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

void PrintAbsyn::visitDef(Def* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_1);
  render("of");
  render("type");
  visitIdent(p->ident_2);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

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

void PrintAbsyn::visitFinal(Final* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("finally");
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

void ShowAbsyn::visitDef(Def* p)
{
  bufAppend('(');
  bufAppend("Def");
  bufAppend(' ');
  visitIdent(p->ident_1);
  bufAppend(' ');
  visitIdent(p->ident_2);
  bufAppend(')');
}
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
void ShowAbsyn::visitFinal(Final* p)
{
  bufAppend('(');
  bufAppend("Final");
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


