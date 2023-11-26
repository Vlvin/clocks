all:
	make ast
	make lox
	make test

buildonly:
	make ast
	make lox

builddebug: Main.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Stmt.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	make ast
	g++ $^ -o lox -g


lox: Main.cpp Environment.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Stmt.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	g++ $^ -o $@

ast: ./toolset/ASTGEN.cpp
	g++ $^ -o $@
	./$@

test: UnitTest.cpp Environment.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Stmt.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	g++ $^ -o $@
	./$@ cases