#include <stdio.h>

#include "debug.h"

void disassembleChunk(Chunk *chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    // Print byte offset
    printf("%04d ", offset);

    // Read a single byte from the bytecode at the given offset, our opcode
    uint8_t instruction = chunk->code[offset];
    // Switch that shit up
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
