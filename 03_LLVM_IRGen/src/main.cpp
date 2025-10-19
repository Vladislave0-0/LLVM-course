#include "../include/generator.hpp"

using namespace LLVM_IRGen;

int main() {
  LLVM_IRGen::Generator generator{"app.c"};
  
  generator.generation();
  generator.dump();
  generator.interpretation();
}
