cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

if (NOT BUILD_MODE)
  set(BUILD_MODE "EXEC")
endif()

message("BUILD_MODE ${BUILD_MODE}")

project(CLocks
        LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
        
set(SOURCEPATH ${PROJECT_SOURCE_DIR}/source)
set(INCLUDE_PATH ${SOURCEPATH})

add_executable(ASTGen ${PROJECT_SOURCE_DIR}/toolset/ASTGEN.cpp)

add_custom_command(
    TARGET ASTGen
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ASTGen
    COMMENT "Build target AST"
    VERBATIM
)

set(SOURCES 
    ${SOURCEPATH}/Clockswork.cpp
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

if (BUILD_MODE STREQUAL "LIB_SHARED")
  set(LIB_TYPE SHARED)
elseif (BUILD_MODE STREQUAL "LIB_STATIC")
  set(LIB_TYPE STATIC)
endif()

if (BUILD_MODE STREQUAL "EXEC")
  add_executable(${PROJECT_NAME} ${SOURCEPATH}/Main.cpp ${SOURCES})
else()
  add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})


