#include "render.h"

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
	int			ibo;

	int			sz_ibo;
	int			sz_vbo;
} mesh_t;

r_mesh_t		ptr_mesh = 0;
mesh_t			pool_mesh[32];

static vframe_t vram;

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
	vbuf_init(&vframe->index, GL_ELEMENT_ARRAY_BUFFER, INDEX_BUFFER_SIZE);
	
	int offset = 0;
	
#ifdef VERTEX_ATTRIB_0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VERTEX_ATTRIB_0, GL_FLOAT, GL_FALSE, VERTEX_SIZE, 0);
	
	offset = offset + VERTEX_ATTRIB_0;
#endif
	
#ifdef VERTEX_ATTRIB_1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VERTEX_ATTRIB_1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (float*) 0 + offset);
	
	offset = offset + VERTEX_ATTRIB_1;
#endif
	
#ifdef VERTEX_ATTRIB_2
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, VERTEX_ATTRIB_2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (float*) 0 + offset);
	
	offset = offset + VERTEX_ATTRIB_2;
#endif

#ifdef VERTEX_ATTRIB_3
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, VERTEX_ATTRIB_3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (float*) 0 + offset);
#endif

}

void r_init_buffer() {
	vframe_init(&vram);
}

void r_add_mesh(r_mesh_t* r_mesh, void* vertex, int vertex_size, void* index, int index_size) {
	mesh_t* mesh = &pool_mesh[ptr_mesh];

	mesh->vbo		= vram.vertex.ptr;
	mesh->sz_vbo	= vertex_size;
	
	int ptr_vertex = vram.vertex.ptr;
	
	vram.vertex.ptr += vertex_size * VERTEX_SIZE;
	
	if (vram.vertex.ptr > VERTEX_BUFFER_SIZE)
		Com_Printf(LOG_ERROR, "failed to allocate to vertex buffer %i/%i", vram.vertex.ptr, VERTEX_BUFFER_SIZE);
	
	glBufferSubData(GL_ARRAY_BUFFER, ptr_vertex, vertex_size * VERTEX_SIZE, vertex);
	
	if (index) {
		mesh->ibo		= vram.index.ptr;
		mesh->sz_ibo	= index_size;
		
		int ptr_index = vram.index.ptr;
		
		vram.index.ptr += index_size * sizeof(int);
		
		if (vram.index.ptr > INDEX_BUFFER_SIZE)
			Com_Printf(LOG_ERROR, "failed to allocate to vertex buffer %i/%i", vram.index.ptr, INDEX_BUFFER_SIZE);
		
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, ptr_index, index_size * sizeof(int), index);
	} else {
		mesh->ibo = 0;
		mesh->sz_ibo = 0;
	}

	*r_mesh = ptr_mesh++;
}

void r_draw_mesh(r_mesh_t r_mesh) {
	mesh_t* mesh = &pool_mesh[r_mesh];

	if (mesh->sz_ibo)
		glDrawElements( GL_TRIANGLES, mesh->sz_ibo, GL_UNSIGNED_INT, (char*) 0 + mesh->ibo );
	else
		glDrawArrays( GL_TRIANGLES, mesh->vbo, mesh->sz_vbo );
}
