#include "../generated/langLexer.h"
#include <../include/IRGenerator.hpp>
#include <CLI/CLI.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <llvm/IR/Verifier.h>
#include <string>

using namespace lang2ir;
namespace fs = std::filesystem;

int main(int argc, char **argv) {
  CLI::App app{"Language to LLVM IR generator"};

  std::string langFile;
  std::string outputFile;

  app.add_option("lang_file", langFile, "Input LANG file")->required();
  auto outOption =
      app.add_option("-o,--output", outputFile, "Output LLVM IR file");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  if (outOption->count() == 0) {
    fs::path inputPath(langFile);
    outputFile = inputPath.replace_extension(".ll").string();
  }

  std::ifstream stream(langFile);
  ANTLRInputStream input(stream);
  langLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  langParser parser(&tokens);

  IRGenerator generator{};
  generator.visitProgram(parser.program());

  std::error_code EC;
  llvm::raw_fd_ostream IRFile(outputFile, EC);
  if (EC) {
    std::cerr << "Error opening file for IR output: " << EC.message()
              << std::endl;
    return 1;
  }

  generator.printModule(IRFile);
  // generator.execute();
}
