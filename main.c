#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

//TODO Fix line counts in disassembly

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // Stores the index of the added constant

  writeConstant(&chunk, 1.2, 125);
  writeConstant(&chunk, 1.5, 125);

  
  writeChunk(&chunk, OP_ADD, 125);

  writeConstant(&chunk, 5.6, 125);

  writeChunk(&chunk, OP_DIVIDE, 125);

  writeChunk(&chunk, OP_NEGATE, 125);
  writeChunk(&chunk, OP_RETURN, 125);
  //disassembleChunk(&chunk, "test");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
