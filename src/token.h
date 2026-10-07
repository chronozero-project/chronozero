#pragma once
#include <cstddef>
#include <string>

enum class tokenKind {
    fn,
    return_,
    if_,
    else_,
    while_,

    i32,
    i64,
    f32,
    f64,
    bool_,
    void_,

    identifier,
    integerLiteral,
    floatLiteral,
    stringLiteral,

    plus,
    minus,
    star,
    slash,
    equal,
    equalEqual,
    notEqual,
    less,
    lessEqual,
    greater,
    greaterEqual,

    leftParen,
    rightParen,
    leftBrace,
    rightBrace,
    comma,
    semicolon,

    endOfFile
};

struct token {
    tokenKind kind;
    std::string text;
    std::size_t line;
    std::size_t column;
};