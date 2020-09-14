#ifndef M_LOCAL_H
#define M_LOCAL_H

typedef struct {
	int*	jmp;
	char*	blk;
	
	int		blksz;
	
	int		ptr;
	int		size;
	int		length;
} pool_t;

void*		Pool_Alloc(pool_t* pool);

typedef struct {
	char*	ptr;
	char*	end;
	char*	block;
	
	int		size;
	
	int		used;
} memhunk_t;

void		Hunk_Init(memhunk_t* hunk, int size);

void*		Hunk_Alloc(memhunk_t* hunk, int size);

void*		Hunk_Ptr(memhunk_t* hunk);

void		Hunk_Reset(memhunk_t* hunk, void* reset);

void		Hunk_Pool_Alloc(memhunk_t* hunk, pool_t* pool, int stride, int size);

#endif
