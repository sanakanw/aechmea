#include "m_local.h"

void pool_init(pool_t* pool, void* blk, int* jmp, int szblk, int size) {
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
	
	return &pool->blk[ptr];
}
