#pragma once
#include <cstddef>
#include <vector>
#include "ast.h"
#include "token.h"

class parser {
public:
    explicit parser(const std::vector<token>& tokens);
    program parce();


private:
    const std::vector<token>& tokens;
    std::size_t position = 0;

    const token& current() const;
    const token& advance();

    bool check(tokenKind kind) const;
    bool match(tokenKind kind);

    const token& expect(tokenKind kind);

    functionDeclaration parseFunction();

    std::unique_ptr<statement> parseStatement();
    std::unique_ptr<statement> parseReturnStatement();
    std::unique_ptr<statement> parseVariableDeclaration();
    std::unique_ptr<expression> parseExpression();
    std::unique_ptr<expression> parsePrimary();

    std::unique_ptr<expression> parseBinaryExpression(
        int minimumPrecedance
        );
    int getPrecedance(tokenKind kind) const;
};