Locals = Resolver.cpp Environment.cpp Interpreter.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Stmt.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp LoxFunction.cpp
Flags = -Wno-pointer-arith -Wno-conversion-null

all:
	make ast
	make lox
	make test

buildonly:
	make ast
	make lox

buildoptimizes: Main.cpp $(Locals)
	make ast
	g++ $^ -o lox -O2

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