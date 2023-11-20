all:
	make ast
	make lox
	make test

buildonly:
	make ast
	make lox

builddebug: Main.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	make ast
	g++ $^ -o $@ -g


lox: Main.cpp  Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	g++ $^ -o $@

ast:
	g++ ./toolset/ASTGEN.cpp -o $@
	./$@

test: UnitTest.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	g++ $^ -o $@
	./$@ cases