CLocks 
===
 CLocks is dialect of lox - dynamic typed, high-level language, made by Robert Nystrom and explained in his book Crafting Interpreters

 Clocks can do everything that lox can and even more.
 
 # Build
  ## Dependencies
  ```CLocks``` depends on Cmake (3.0.2+)

  ## Instalation
  In general you need to download ```CLocks``` project, enter directory contains it, then build it using cmake
  ```bash
     git clone https://github.com/Vlvin/clocks.git
     cd clocks
     mkdir build
     cd build
     cmake ../
     cmake --build .
  ```

  Now in clocks/bin/ directory you have built CLocks executable file


CLocks abilities
===
 Literal Types
 - NUMBER : represents real number (6 digits after floating point)
     - can be used in all math operations
 - STRING : represents string of character
     - can be created with using "" syntax
     - can be concatenated with other string using "+" sign
 - BOOLEAN : represents logical number
     - can have two states: true and false
 - CALLABLE : represents callable
     - callable is function or class
     - can be called using call operator "()"
 - INSTANCE : represents object of class
     - '.' can be used to access to fields of instance
     - field can be assigned with using '=' operator
     - field with using no operator will return it's value
 - NIL : represents Not Initialized Literal
     - variable holds NIL can be assigned to anything even if constant
     
 Math
 - Constants
     - PI = 3.14
     - E = 2.71
 - Binary operations
     - '=' : for assignment
     - '+' : for addition
     - '-' : for substraction
     - '/' : for division
     - '*' : for multiplication
     - '%' : for modulo division
 - Logical operators:
     - '==' : for equality check
     - '!=' : for not equality check
     - '!' : for negation 
     - and : for conjunction 
     - or : for disjunction 
 - Comparison operators:
     - '<' : for less than
     - '>' : for greater than
     - '<=' : for less-equals
     - '>=' : for greater-equals
 - Unary oparators
     - "-" : NUMBER negation
     - "!" : BOOLEAN negation

 Standart Library
 - I/O
     - print(...) : prints out argues separated by space character, with Enter character at the end
     - input(...) : prints out argues separated by space character and waits for input, converting it to a NUMBER if it can
 - Math
     - sin(n) : returns sine of n degrees
     - cos(n) : returns cosine of n degrees
     - radSin(n) : returns sine of n radians
     - radCos(n) : returns cosine of n radians
     - radToDeg(n) : converts n radians to degrees
     - degToRad(n) : converts n degrees to radians
 - Work with types and classes
     - type(n) : returns type of variable n, as a string literal
     - instanceOf(n) : returns class name of instance n
     - superName(n) : returns superclass name of instance or class n, if it exists
 - Other stuff
     - exit(n) : exit from program with code n if it was passed, otherwise 0
     - clock() : returns time of day in seconds
 
 
 Statement operators
 - if (condition) {consequent} : execute consequent if condition is true
 - else {alternative} : used after if, execute alternative if condition is false
 - while (condition) {consequent} : execute consequent while condition is true
 - for (variable with initializer; condition; increment) {consequent} : initialize variable with initializer (ifw it exists) execute consequent, uses increment, repeat until condition is true
 

 Variables
 - Definition: defined with using "var" keyword followed with identifier as its name
 - Initialization: before first assignment, variable gets type NIL
 - Assignment: variable can be assignment to any literal with using '=' operator followed by literal or identifier
 - Get: variable name returns its value
 - Constant: "const" keyword before variable definition means that after Initialization this variable couldn't be changed
 
 Functions
 - Definition and initialization: defined with using "fun" keyword followed with identifier, parenthesis contains arguements list, and braces contains function body
 - Return: "return" keyword followed by literal or identifier finishes function execution and returns literal or identifier, if it exists, nil otherwise
 - Recurtion: function can be called even in its own body (warning: without "default case" it can cause endless recurtion)
 
 Classes
 - Definition and initialization: defined with using "class" keyword folowed with identifier and braces contains class body
 - Instantiantion: call of class returns an instance of this class
 - Method declaration: when function declaration "fun" keyword, method doesn't, it declared using just identifier
 - Constructor: method with name "constructor" called on Instantiation, if it exists
 - Fields declaration and assignment: inside of class methods, use "this" keyword followed by '.' and identifier to declare field, then assign it with using '=' operator
 - Static methods: "static" keyword before method declaration means this method have no "this" binding, and can be called directrly from class 
 - Inheritance: class can inherit from other class with operator '<', in this case it gets all methods of superclass, and it's own methods now have keyword "super" which returns superclass

- Others
 - log: log statement followed by identifier of literal, prints it out