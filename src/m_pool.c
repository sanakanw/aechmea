#include "memory.h"

#include <stdio.h>

void* Pool_Alloc(pool_t* pool) {
	pool->length++;
	
	int ptr = pool->ptr;
	
	pool->ptr += pool->blksz; 
	
	return &pool->blk[ptr];
}
