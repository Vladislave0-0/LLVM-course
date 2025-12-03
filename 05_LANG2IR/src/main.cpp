#include <../include/visitor.hpp>
// #include <../include/IRGenerator.hpp>
#include <CLI/CLI.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace lang2ir;

int main(int argc, char **argv) {
  CLI::App app{"Language to LLVM IR generator"};

  std::string langFile;
  std::string outputFile = "output.ll";

  app.add_option("lang_file", langFile, "Input LANG file")->required();
  app.add_option("-o,--output", outputFile, "Output LLVM IR file");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  std::ifstream stream(langFile);
  ANTLRInputStream input(stream);
  langLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  langParser parser(&tokens);

  try {
    auto tree = parser.prog();
    LangVisitor visitor;
    int result = std::any_cast<int>(visitor.visit(tree));
    std::cout << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error parsing expression: " << e.what() << std::endl;
  }

  // std::unique_ptr<IRGenerator> generator;
}
