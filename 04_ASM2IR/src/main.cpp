#include "../include/EmulateIR.hpp"
#include "../include/FullIR.hpp"

#include <CLI/CLI.hpp>
#include <llvm/IR/Verifier.h>

using namespace asm2ir;

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

  AsmParser parser{asmFile};
  if (!parser.parse()) {
    std::cerr << "\nFailed to parse ASM file: " << asmFile << std::endl;
    return 1;
  }

  std::cout << "Successfully parsed " << parser.instructions.size()
            << " instructions." << std::endl;

  std::unique_ptr<IRGenerator> generator;

  if (emulateMode) {
    generator = std::make_unique<EmulateIRGenerator>();
  } else {
    generator = std::make_unique<FullIRGenerator>();
  }

  generator->buildIR(parser);
  if (llvm::verifyModule(*generator->getIRModule(), &outs())) {
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

  generator->getIRModule()->print(IRFile, nullptr);
  IRFile.flush();
  std::cout << "LLVM IR successfully written to " << outputFile << std::endl;

  CPU cpu;
  generator->execute(cpu);
}
