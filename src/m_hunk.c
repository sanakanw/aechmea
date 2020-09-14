#include "memory.h"

#include "common.h"

#include <string.h>

void Hunk_Init(memhunk_t* hunk, int size) {
	hunk->used = 0;
	hunk->size = size;

	hunk->block	= malloc(size);
	hunk->ptr	= hunk->block;
	hunk->end	= hunk->block + size;
}

void* Hunk_Ptr(memhunk_t* hunk) {
	return hunk->ptr;
}

void Hunk_Reset(memhunk_t* hunk, void* pointer) {
	char* ptr = (char*) pointer;

	if (ptr < hunk->block || ptr > hunk->end)
		Com_Printf(LOG_ERROR, "Hunk reset out of bounds.");

	hunk->ptr = ptr;
}

void* Hunk_Alloc(memhunk_t* hunk, int size) {
	void* ptr = (void*) hunk->ptr;

	hunk->used += size;

	if ((hunk->ptr += size) > hunk->end)
		Com_Printf(LOG_ERROR, "Could not allocate to hunk. %i / %i", hunk->used, hunk->size);
	
	return ptr;
}

void Hunk_Pool_Alloc(memhunk_t* hunk, pool_t* pool, int blksz, int size) {
	pool->jmp		= Hunk_Alloc(hunk, (sizeof(int) + blksz) * size);
	pool->blk		= (char*) (pool->jmp + size);
	pool->blksz		= blksz;
	pool->size		= size;
	pool->length	= 0;
	pool->ptr		= 0;
}
