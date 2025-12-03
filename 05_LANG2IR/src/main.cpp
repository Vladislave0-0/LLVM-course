#include "../generated/langLexer.h"
#include <../include/IRGenerator.hpp>
// #include <../include/visitor.hpp>
#include <CLI/CLI.hpp>
#include <fstream>
#include <iostream>
#include <llvm/IR/Verifier.h>
#include <string>

using namespace lang2ir;

int main(int argc, char **argv) {
  CLI::App app{"Language to LLVM IR generator"};

  std::string langFile;
  std::string outputFile = "app.ll";

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

  IRGenerator generator{};
  generator.buildIR(parser);
  if (llvm::verifyModule(*generator.getIRModule(), &outs())) {
    std::cout << "[Verification] Failed." << std::endl;
    return 1;
  }

  std::error_code EC;
  llvm::raw_fd_ostream IRFile(outputFile, EC);
  if (EC) {
    std::cerr << "Error opening file for IR output: " << EC.message()
              << std::endl;
    return 1;
  }

  generator.getIRModule()->print(IRFile, nullptr);

  // generator.execute();
}
