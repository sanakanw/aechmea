#ifndef M_LOCAL_H
#define M_LOCAL_H

typedef struct {
	int*	jmp;
	int		ptr;
	int		size;
	int		length;
} pool_t;

int			Pool_Alloc(pool_t* pool);

void		Pool_Free(pool_t* pool, int i);


void		Hunk_Init(int size);

void		Hunk_Reset(void* pointer);

void*		Hunk_Alloc(int size);

void*		Hunk_Pointer();

void		Hunk_Alloc_Pool(pool_t** pool, int size);

#endif
