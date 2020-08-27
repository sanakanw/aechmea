#include "r_local.h"

typedef GLuint	block_t;

r_block_t		ptr_block = 0;
block_t			pool_block[32];

void R_Add_Block(r_block_t* r_block, int size) {
	glGenBuffers(1, &pool_block[ptr_block]);

	glBindBuffer(GL_UNIFORM_BUFFER, pool_block[ptr_block]);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, ptr_block, pool_block[ptr_block], 0, size);

	*r_block = ptr_block++;
}

void R_Block_SubData(r_block_t block, void* data, int offset, int size) {
	glBindBuffer(GL_UNIFORM_BUFFER, pool_block[block]);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}
