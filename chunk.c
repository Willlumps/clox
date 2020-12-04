#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

// Inititalize empty chunk
void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

// Frees a chunk from memory
void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    //FREE_ARRAY(int, chunk->lines, chunk->capacity);
    FREE_ARRAY(LineStart, chunk->lines, chunk->lineCapacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

// Append to a chunk
void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    // If the chunk is currently full, expand it by a factor of two
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
    }

    // Store the byte and line number
    chunk->code[chunk->count] = byte;
    chunk->count++;

    // Are we on the same line?
    if (chunk->lineCount > 0 &&
        chunk->lines[chunk->lineCount - 1].line == line) {
        return;
    }

    // Append a new LineStart, growing the array if needed.
    if (chunk->lineCapacity < chunk->lineCount + 1) {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(LineStart, chunk->lines,
            oldCapacity, chunk->lineCapacity);
    }

    LineStart *linestart = &chunk->lines[chunk->lineCount++];
    linestart->offset = chunk->count + 1;
    linestart->line = line;
}

// Append a constant to a chunk
int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int instruction) {
    int start = 0;
    int end = chunk->lineCount - 1;

    for (;;) {
        int mid = (start + end) / 2;
        LineStart *line = &chunk->lines[mid];
        if (mid == chunk->lineCount - 1 ||
            instruction < chunk->lines[mid + 1].offset) {
            return line->line;
        } else if(instruction < line->offset) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
}
