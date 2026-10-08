cmake_minimum_required(VERSION 3.20)

project(Chronos
    VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(chronozero
    main.cpp
        src/token.h
        src/token.cpp
        src/lexer.cpp
        src/lexer.h
        src/ast.h
        src/parser.h
)