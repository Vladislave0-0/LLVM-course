#include <../include/visitor.hpp>
#include <fstream>
#include <iostream>

using namespace lang2ir;

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);
  ANTLRInputStream input(stream);
  langLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  langParser parser(&tokens);

  parser.removeErrorListeners();

  try {
    auto tree = parser.prog();
    LangVisitor visitor;
    int result = std::any_cast<int>(visitor.visit(tree));
    std::cout << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error parsing expression: " << e.what() << std::endl;
  }
}
