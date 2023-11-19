all:
	make ast
	make lox

lox: Main.cpp Scanner.cpp ASTPrinter.cpp Clockswork.cpp Expr.cpp Parser.cpp Token.cpp TokenLiteral.cpp
	g++ $^ -o $@

ast:
	g++ ./toolset/ASTGEN.cpp -o $@
	./$@