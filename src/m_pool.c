#include "m_local.h"

void pool_init(pool_t* pool, void* blk, int* jmp, int size, int szblk) {
	pool->blk	= blk;
	pool->jmp	= jmp;
	pool->size	= size;
	pool->szblk	= szblk;
	
	pool->ptr		= 0;
	pool->length	= 0;

	memset(pool->jmp, 0, pool->size * sizeof(int));
}

void* pool_alloc(pool_t* pool) {
	int ptr = pool->ptr;

	if (pool->jmp[ptr] > 0) {
		pool->ptr = pool->jmp[ptr];
		pool->jmp[ptr] = 0;
	} else {
		pool->ptr++;
		pool->length++;
		
		if (pool->length == pool->size)
			com_printf(LOG_ERROR, "pool: failed to allocate %i/%i", pool->length, pool->size);
	}

	com_printf(LOG_DEBUG, "pool: alloc %i/%i", ptr, pool->size);

	return &pool->blk[ptr * pool->szblk];
}

void pool_remove(pool_t* pool, int ptr) {
	if (ptr == pool->length - 1) {
		if (pool->ptr == pool->length)
			pool->length--;
		else {
			pool->jmp[ptr] = pool->ptr;
			pool->ptr = ptr;
		}

		pool->ptr--;
	} else {
		pool->jmp[ptr] = pool->ptr;
		pool->ptr = ptr;
	}

	com_printf(LOG_DEBUG, "pool: remove; ptr: %i/%i", pool->ptr, pool->size);
}

int pool_is_alloc(pool_t* pool, int i) {
	return (i < pool->length && pool->jmp[i] == 0);
}

void* pool_get(pool_t* pool, int i) {
	return &pool->blk[i * pool->szblk];
}
