#include "m_local.h"

void pool_init(pool_t* pool, void* blk, int* jmp, int size, int szblk) {
	pool->blk	= blk;
	pool->jmp	= jmp;
	pool->size	= size;
	pool->szblk	= szblk;
	
	pool->ptr		= 0;
	pool->length	= 0;
}

void* pool_alloc(pool_t* pool) {
	pool->length++;
	
	int ptr = pool->ptr;
	
	pool->ptr += pool->szblk;

	if (pool->length >= pool->size) {
		Com_Printf(LOG_ERROR, "pool: failed to allocate %i\%i", pool->length, pool->size);

		return NULL;
	}
	
	return &pool->blk[ptr];
}

void* pool_get(pool_t* pool, int i) {
	return &pool->blk[i * pool->szblk];
}
