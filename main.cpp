#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include "src/lexer.h"

const char* tokenKindToString(tokenKind kind) {
    switch (kind) {
    case tokenKind::fn:
        return "fn";
    case tokenKind::return_:
        return "return";
    case tokenKind::i32:
        return "i32";
    case tokenKind::i64:
        return "i64";
    case tokenKind::f32:
        return "f32";
    case tokenKind::f64:
        return "f64";
    case tokenKind::bool_:
        return "bool";
    case tokenKind::void_:
        return "void";
    case tokenKind::identifier:
        return "identifier";
    case tokenKind::integerLiteral:
        return "integerLiteral";
    case tokenKind::leftParen:
        return "leftParen";
    case tokenKind::rightParen:
        return "rightParen";
    case tokenKind::leftBrace:
        return "leftBrace";
    case tokenKind::rightBrace:
        return "rightBrace";
    case tokenKind::semicolon:
        return "semicolon";
    case tokenKind::endOfFile:
        return "EOF";
    default:
        return "unknown";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chronos <file.crn>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Chronos: Can't open file: " << argv[1] << std::endl;
        return 1;
    }
    const std::string source(
        std::istreambuf_iterator<char>(file),
        {}
        );
    try {
        lexer lexer(source);
        const auto tokens = lexer.tokenize();
        for (const auto& token : tokens) {
            std::cout
            << token.line << ":"
            << token.column << " "
            << tokenKindToString(token.kind) << "\""
            << token.text << std::endl;
        }
    }catch (const std::exception& e) {
        std::cerr << "Chronos: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}