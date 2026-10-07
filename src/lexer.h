#pragma once
#include <string>
#include <vector>
#include "token.h"

class lexer {
    public:
    explicit lexer(const std::string& source);
    std::vector<token> tokenize();

    private:
    const std::string& source;

    std::size_t position = 0;
    std::size_t line = 1;
    std::size_t column = 1;

    char peek() const;
    char advance();
    void skipWhitespace();

    token makeToken(
        tokenKind kind,
        const std::string& text,
        std::size_t tokenLine,
        std::size_t tokenColumn
    );
};