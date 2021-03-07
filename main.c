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
  writeConstant(&chunk, 155, 10);
  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 1.3, 124);
  writeConstant(&chunk, 1.4, 124);
  writeConstant(&chunk, 1.5, 125);

  writeChunk(&chunk, OP_RETURN, 125);
  writeChunk(&chunk, OP_RETURN, 125);
  disassembleChunk(&chunk, "test");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
