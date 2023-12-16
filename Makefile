Locals = Environment.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Stmt.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
Flags = -Wno-pointer-arith -Wno-conversion-null

all:
	make ast
	make lox
	make test

buildonly:
	make ast
	make lox

builddebug: Main.cpp $(Locals)
	make ast
	g++ $^ -o lox -g


lox: Main.cpp $(Locals)
	g++ $^ -o $@ $(Flags)

ast: ./toolset/ASTGEN.cpp
	g++ $^ -o $@
	./$@

test: UnitTest.cpp $(Locals)
	./$@ cases