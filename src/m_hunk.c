#include "memory.h"

#include "common.h"

#include <string.h>

void hunk_init(memhunk_t* hunk, int size) {
	hunk->used = 0;
	hunk->size = size;

	hunk->block	= malloc(size);
	hunk->ptr	= hunk->block;
	hunk->end	= hunk->block + size;
}

void* hunk_ptr(memhunk_t* hunk) {
	return hunk->ptr;
}

void hunk_reset(memhunk_t* hunk, void* pointer) {
	char* ptr = (char*) pointer;

	if (ptr < hunk->block || ptr > hunk->end)
		Com_Printf(LOG_ERROR, "Hunk reset out of bounds.");
	
	hunk->ptr = ptr;
	
	hunk->used = ptr - hunk->block;
}

void* hunk_alloc(memhunk_t* hunk, int size) {
	void* ptr = (void*) hunk->ptr;

	hunk->used += size;

	if ((hunk->ptr += size) > hunk->end)
		Com_Printf(LOG_ERROR, "Could not allocate to hunk. %i / %i", hunk->used, hunk->size);
	
	return ptr;
}

void hunk_pool_alloc(memhunk_t* hunk, pool_t* pool, int szblk, int size) {
	pool->jmp		= hunk_alloc(hunk, (sizeof(int) + szblk) * size);
	pool->blk		= (char*) (pool->jmp + size);
	pool->szblk		= szblk;
	pool->size		= size;
	pool->length	= 0;
	pool->ptr		= 0;
}
