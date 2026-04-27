#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: netxlang <file.nxl>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    try {
        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        auto ast = parser.parse();

        SemanticAnalyzer analyzer;
        analyzer.analyze(ast.get());

        Interpreter interpreter;
        std::cout << "--- NetXLang Simulation Started ---\n";
        interpreter.interpret(ast.get());
        std::cout << "--- NetXLang Simulation Ended ---\n";

    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
