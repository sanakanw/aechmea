#ifndef MEMORY_H
#define MEMORY_H

#define kb(x) x * 1024
#define mb(x) x * 1024 * 1024

typedef struct {
	int*	jmp;
	char*	blk;
	
	int		szblk;
	
	int		ptr;
	int		size;
	int		length;
} pool_t;

void		pool_init(pool_t* pool, void* blk, int* jmp, int size, int szblk);

void*		pool_alloc(pool_t* pool);

void*		pool_get(pool_t* pool, int i);

typedef struct {
	char*	ptr;
	char*	end;
	char*	block;
	
	int		size;
	
	int		used;
} memhunk_t;

void		hunk_init(memhunk_t* hunk, int size);

void*		hunk_alloc(memhunk_t* hunk, int size);

void*		hunk_ptr(memhunk_t* hunk);

void		hunk_reset(memhunk_t* hunk, void* reset);

void		hunk_pool_alloc(memhunk_t* hunk, pool_t* pool, int size, int sizeblk);

#endif
