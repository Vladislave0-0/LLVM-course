#include "../include/AsmParser.hpp"
#include "../include/IRGenerator.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <asm_file> [output_file.ll]"
              << std::endl;
    return 1;
  }

  std::string asmFile = argv[1];
  std::string outputFile = (argc > 2) ? argv[2] : "output.ll";

  asm2ir::AsmParser parser{asmFile};
  if (!parser.parse()) {
    std::cerr << "Failed to parse ASM file: " << asmFile << std::endl;
    return 1;
  }

  std::cout << "Successfully parsed " << parser.getInstructions().size()
            << " instructions." << std::endl;

  asm2ir::IRGenerator generator;
  generator.generate(parser.getInstructions(), parser.getLabels());

  generator.writeToFile(outputFile);

  std::cout << "LLVM IR generated successfully: " << outputFile << std::endl;
}