#include "memory.h"

#include <stdio.h>

void* pool_alloc(pool_t* pool) {
	pool->length++;
	
	int ptr = pool->ptr;
	
	pool->ptr += pool->szblk; 
	
	return &pool->blk[ptr];
}
