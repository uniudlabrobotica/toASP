CC = g++
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PCalc

BISON = bison
BISON_OPTS = -t -pCalc

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestCalc

clean:
	rm -f *.o TestCalc Calc.aux Calc.log Calc.pdf Calc.dvi Calc.ps Calc

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile Calc.l Calc.y Calc.tex 

TestCalc: ${OBJS} Test.o
	@echo "Linking TestCalc..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestCalc

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Calc.l
	${FLEX} -oLexer.C Calc.l

Parser.C: Calc.y
	${BISON} Calc.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

