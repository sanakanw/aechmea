#include "m_local.h"

#include "qcommon.h"

#include <string.h>

typedef struct {
	char*	block;
	char*	ptr;
	char*	end;
	
	int		used;
	int		size;
} memhunk_t;

static memhunk_t hunk;

void Hunk_Init(int size) {
	hunk.used = 0;
	hunk.size = size;

	hunk.block	= malloc(size);
	hunk.ptr	= hunk.block;
	hunk.end	= hunk.block + size;
}

void Hunk_Reset(void* pointer) {
	char* ptr = (char*) pointer;

	if (ptr < hunk.block || ptr > hunk.end)
		Com_Printf(LOG_ERROR, "Hunk reset out of bounds.");

	hunk.ptr = ptr;
}

void* Hunk_Alloc(int size) {
	void* ptr = (void*) hunk.ptr;

	hunk.used += size;

	if ((hunk.ptr += size) > hunk.end)
		Com_Printf(LOG_ERROR, "Could not allocate to hunk. %i / %i", hunk.used, hunk.size);
	
	return ptr;
}

void* Hunk_Pointer() {
	return (void*) hunk.ptr;
}

void Hunk_Alloc_Pool(pool_t** pool, int size) {
	int jmp_size = size * sizeof(int);

	*pool = Hunk_Alloc(sizeof(pool_t) + jmp_size);
		(*pool)->jmp	= (int*) pool + sizeof(pool_t);
		(*pool)->size	= size;
		(*pool)->length	= 0;
		(*pool)->ptr	= 0;
}
