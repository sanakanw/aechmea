#include "m_local.h"

int Pool_Alloc(pool_t* pool) {
	pool->length++;
	
	return pool->ptr++;
}
