#include "../include/generator.hpp"

using namespace LLVM_IRGen;

int main() {
  LLVM_IRGen::Generator generator;

  generator.generation();
  generator.dump();
  
  if (generator.verifyModule_())
    generator.interpretation();
}
