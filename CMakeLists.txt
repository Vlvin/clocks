cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project(CLocks
        LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/archive)
        
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR})
set(SOURCEPATH ${PROJECT_SOURCE_DIR}/source)

add_executable(ASTGen ${PROJECT_SOURCE_DIR}/toolset/ASTGEN.cpp)

add_custom_command(
    TARGET ASTGen
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ASTGen
    COMMENT "Build target AST"
    VERBATIM
)

set(SOURCES 
    ${SOURCEPATH}/Clockswork.cpp
    ${SOURCEPATH}/Main.cpp
    ${SOURCEPATH}/Token.cpp
    ${SOURCEPATH}/TokenLiteral.cpp
    ${SOURCEPATH}/Scanner.cpp
    ${SOURCEPATH}/Parser.cpp
    ${SOURCEPATH}/Expr.cpp
    ${SOURCEPATH}/Stmt.cpp
    ${SOURCEPATH}/Resolver.cpp
    ${SOURCEPATH}/Interpreter.cpp
    ${SOURCEPATH}/Environment.cpp
    ${SOURCEPATH}/LoxFunction.cpp
    ${SOURCEPATH}/LoxClass.cpp
    ${SOURCEPATH}/LoxInstance.cpp)

add_executable(CLocks ${SOURCES})

target_include_directories(CLocks PUBLIC ${INCLUDE_PATH})


