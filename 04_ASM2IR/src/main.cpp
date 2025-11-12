#include "../include/AsmParser.hpp"
// #include "../include/IRGenerator.hpp"

#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  CLI::App app{"ASM to LLVM IR generator"};

  std::string asmFile;
  std::string outputFile = "output.ll";
  bool emulateMode = false;

  app.add_option("asm_file", asmFile, "Input ASM file")->required();
  app.add_option("-o,--output", outputFile, "Output LLVM IR file");
  app.add_flag("-e,--emulate", emulateMode,
               "Generate IR with emulation function calls");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  asm2ir::AsmParser parser{asmFile};
  if (!parser.parse()) {
    std::cerr << "Failed to parse ASM file: " << asmFile << std::endl;
    return 1;
  }

  std::cout << "Successfully parsed " << parser.getInstructions().size()
            << " instructions." << std::endl;
}
