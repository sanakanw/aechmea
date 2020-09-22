#include "r_local.h"

typedef struct {
	GLuint		id;

	int			ptr;
	int			size;
} vbuf_t;

typedef struct {
	GLuint		vao;

	vbuf_t		index;
	vbuf_t		vertex;
} vframe_t;

typedef struct {
	int			vbo;
	int			szvbo;
} mesh_t;

r_mesh_t		ptr_mesh = 0;
mesh_t			pool_mesh[32];

static			vframe_t vram;

int				vertex_size = 0;

void vbuf_init(vbuf_t* vbuf, GLuint type, int size) {
	vbuf->ptr	= 0;
	vbuf->size	= size;

	glGenBuffers(1, &vbuf->id);
	glBindBuffer(type, vbuf->id);
	glBufferData(type, vbuf->size, 0, GL_DYNAMIC_DRAW);
}

void vframe_init(vframe_t* vframe) {
	glGenVertexArrays(1, &vframe->vao);
	glBindVertexArray(vframe->vao);

	vbuf_init(&vframe->vertex, GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE);
	
	int offset = 0;
	int stride = VERTEX_SIZE;
	
#ifdef VERTEX_ATTRIB_0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VERTEX_ATTRIB_0, GL_FLOAT, GL_FALSE, stride, 0);
	
	offset = offset + VERTEX_ATTRIB_0;
#endif
	
#ifdef VERTEX_ATTRIB_1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VERTEX_ATTRIB_1, GL_FLOAT, GL_FALSE, stride, (float*) 0 + offset);
	
	offset = offset + VERTEX_ATTRIB_1;
#endif
	
#ifdef VERTEX_ATTRIB_2
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, VERTEX_ATTRIB_2, GL_FLOAT, GL_FALSE, stride, (float*) 0 + offset);
	
	offset = offset + VERTEX_ATTRIB_2;
#endif

#ifdef VERTEX_ATTRIB_3
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, VERTEX_ATTRIB_3, GL_FLOAT, GL_FALSE, stride, (float*) 0 + offset);
#endif
	
}

void r_init_buffer() {
	vframe_init(&vram);
}

r_mesh_t r_add_mesh(float* vertex, int vbufsz) {
	mesh_t* mesh = &pool_mesh[ptr_mesh];
	
	mesh->vbo	= vram.vertex.ptr / VERTEX_SIZE;
	mesh->szvbo	= vbufsz;
	
	int ptr_vertex = vram.vertex.ptr;

	vram.vertex.ptr += vbufsz * VERTEX_SIZE;
	
	if (vram.vertex.ptr > VERTEX_BUFFER_SIZE)
		com_printf(LOG_ERROR, "failed to allocate to vertex buffer %i/%i", vram.vertex.ptr, VERTEX_BUFFER_SIZE);
	
	glBufferSubData(GL_ARRAY_BUFFER, ptr_vertex, vbufsz * VERTEX_SIZE, vertex);

	return ptr_mesh++;
}

void r_draw_mesh(r_mesh_t r_mesh) {
	mesh_t* mesh = &pool_mesh[r_mesh];
	
	glDrawArrays( GL_TRIANGLES, mesh->vbo, mesh->szvbo );
}
