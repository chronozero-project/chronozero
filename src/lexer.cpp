#include "lexer.h"
#include <cctype>
#include <stdexcept>

lexer::lexer(const std::string& source)
    : source(source) {
}

char lexer::peek() const {
    if (position >= source.size()) {
        return '\0';
    }
    return source[position];
}

char lexer::advance() {
    const char c = peek();
    if (c == '\0') {
        return c;
    };
    ++position;
    if (c == '\n') {
        ++line;
        column = 1;
    }else {
        ++column;
    }
    return c;
}

void lexer::skipWhitespace() {
    while (std::isspace(static_cast<unsigned char>(peek()))) {
        advance();
    }
}

token lexer::makeToken(
    tokenKind kind,
    const std::string& text,
    std::size_t tokenLine,
    std::size_t tokenColumn
) {
    return token{
        kind,
        text,
        tokenLine,
        tokenColumn
    };
}

std::vector<token> lexer::tokenize() {
    std::vector<token> tokens;
    while (true) {
        skipWhitespace();
        const std::size_t tokenLine = line;
        const std::size_t tokenColumn = column;
        if (peek() == '\0') {
            tokens.push_back(
                makeToken(
                    tokenKind::endOfFile,
                    "",
                    tokenLine,
                    tokenColumn
                    ));
            break;
        }
        const char c = advance();
        switch (c) {
        case '(':
            tokens.push_back(
                makeToken(
                    tokenKind::leftParen,
                    "(",
                    tokenLine,
                    tokenColumn
                    ));
            break;
        case ')':
            tokens.push_back(
                makeToken(
                    tokenKind::rightParen,
                    ")",
                    tokenLine,
                    tokenColumn
                    ));
            break;
        case '{':
            tokens.push_back(
                makeToken(
                    tokenKind::leftBrace,
                    "{",
                    tokenLine,
                    tokenColumn
                    ));
            break;
        case '}':
            tokens.push_back(
                makeToken(
                    tokenKind::rightBrace,
                    "}",
                    tokenLine,
                    tokenColumn
                    ));
            break;
        case ';':
            tokens.push_back(
                makeToken(
                    tokenKind::semicolon,
                    ";",
                    tokenLine,
                    tokenColumn
                    ));
            break;

        default:
            if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
                std::string text (1, c);

                while (
                    std::isalnum(static_cast<unsigned char>(peek())) ||
                    peek() == '_'
                    ) {
                    text += advance();
                }
                tokenKind kind;
                if (text == "fn") kind = tokenKind::fn;
                else if (text == "return") kind = tokenKind::return_;
                else if (text == "i32") kind = tokenKind::i32;
                else if (text == "i64") kind = tokenKind::i64;
                else if (text == "f32") kind = tokenKind::f32;
                else if (text == "f64") kind = tokenKind::f64;
                else if (text == "bool") kind = tokenKind::bool_;
                else if (text == "void") kind = tokenKind::void_;
                else kind = tokenKind::identifier;
                tokens.push_back(
                    makeToken(
                        kind,
                        text,
                        tokenLine,
                        tokenColumn
                        ));
            }else if (std::isdigit(
                static_cast<unsigned char>(c)
                )) {
                std::string text (1, c);
                while (
                    std::isdigit(
                        static_cast<unsigned char>(peek())
                        )) {
                    text += advance();
                }

                tokens.push_back(
                    makeToken(
                        tokenKind::integerLiteral,
                        text,
                        tokenLine,
                        tokenColumn
                        ));
            }else {
                throw std::runtime_error(
                    "unexpected character at " +
                    std::to_string(tokenLine) +
                    ":" +
                    std::to_string(tokenColumn));
            }
        }
    }
    return tokens;
}