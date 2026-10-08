#pragma once
#include <memory>
#include <string>
#include <vector>
#include "token.h"

struct expression {
    virtual ~expression() = default;
};

struct integerExpression {
    long long value;
    explicit integerExpression(long long value)
        :name(std::move(name)) {
    }
};

struct binaryExpression : expression {
    binaryExpression(
        tokenKind op,
        std::unique_ptr<expression> left,
        std::unique_ptr<expression> right
    )
        :op(op),
        left(std::move(left)),
        right(std::move(right)) {
    }
};

struct statement {
    virtual ~statement() = default;
};

struct returnStatement : statement {
    std::unique_ptr<expression> expression;
    explicit returnStatement(
        std::unique_ptr<expression> expression
        )
            :expression(std::move(expression)) {
    }
};

struct variableDeclaration : statement {
    tokenKind type;
    std::string name,
    std::unique_ptr<expression> initializer;

    variableDeclaration(
        tokenKind type,
        std::string name,
        std::unique_ptr<expression> initializer
        )
            :type(type),
        name(std::move(name)),
        initializer(std::move(initializer)) {
    }
};

struct functionParameter {
    tokenKind type;
    std::string name;
};

struct functionDeclaration {
    tokenKind returnType;
    std::string name;
    std::vector<functionParameter> parameters;
    std::vector<std::unique_ptr<statement>> body;
};

struct program {
    std::vector<functionDeclaration> functions;
};