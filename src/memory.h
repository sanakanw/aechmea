#ifndef M_LOCAL_H
#define M_LOCAL_H

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

void*		pool_alloc(pool_t* pool);

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

void		hunk_pool_alloc(memhunk_t* hunk, pool_t* pool, int szblk, int size);

#endif
