#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitProgram(Program* p);
  void visitDecl(Decl* p);
  void visitPredicate(Predicate* p);
  void visitLiteral(Literal* p);
  void visitAction(Action* p);
  void visitPrg(Prg* p);
  void visitDef(Def* p);
  void visitExec(Exec* p);
  void visitCaus(Caus* p);
  void visitCausCond(CausCond* p);
  void visitInit(Init* p);
  void visitFinal(Final* p);
  void visitPreds(Preds* p);
  void visitPred(Pred* p);
  void visitLitN(LitN* p);
  void visitLit(Lit* p);
  void visitActs(Acts* p);
  void visitAct(Act* p);
  void visitListLiteral(ListLiteral* p);
  void visitListIdent(ListIdent* p);
  void visitListDecl(ListDecl* p);

  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};


#endif
