#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

// Print the name of the opcode and return the next byte offset
// past the instruction.
static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

// Prints the value of a contant instruction and returns the offset
// of the next instruction.
static int constantInstruction(const char* name, Chunk *chunk, int offset) {
    // Constant value pulled the subsequent byte in the chunk
    uint8_t constant = chunk->code[offset + 1];
    // Print the index and value of the constant
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    // Return the value of the next instruction.
    // In this case it is two, one for the op code
    // and one for the operand.
    return offset + 2;
}

static int longConstantInstruction(const char* name, Chunk *chunk, int offset) {
    uint32_t constant = chunk->code[offset + 1] |
                       (chunk->code[offset + 2] << 8) |
                       (chunk->code[offset + 3] << 16);

    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 4;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    // Print byte offset
    printf("%04d ", offset);

    // Indicate the line number as a "|" if the instruction comes from
    // the same source line as the preceeding one.
    int line = getLine(chunk, offset);
    if (offset > 0 && line == getLine(chunk, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", line);
    }

    // Read a single byte from the bytecode at the given offset, our opcode
    uint8_t instruction = chunk->code[offset];
    // Switch that shit up
    switch (instruction) {
      case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
      case OP_CONSTANT_LONG:
        return longConstantInstruction("OP_CONSTANT_LONG", chunk, offset);
      case OP_ADD:
        return simpleInstruction("OP_ADD", offset);
      case OP_SUBTRACT:
        return simpleInstruction("OP_SUBTRACT", offset);
      case OP_MULTIPLY:
        return simpleInstruction("OP_MULTIPLY", offset);
      case OP_DIVIDE:
        return simpleInstruction("OP_DIVIDE", offset);
      case OP_NEGATE:
        return simpleInstruction("OP_NEGATE", offset);
      case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
      default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}
