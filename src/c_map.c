#include "c_local.h"

typedef enum {
	C_MAP_WALL		= 0b00010000,
	C_MAP_FLOOR		= 0b00100000,
	C_MAP_SOLID		= 0b01000000,
	C_MAP_OPAQUE	= 0b10000000,
} cmap_block_t;

void c_map_push_wall(sbuf_t* vertex, vec3_t p, vec3_t n, vec3_t t, int uv_x, int uv_y) {
	vec3_t b;

	float *v, *vn, *vt;

	float xc, yc, xx, yy;

	vec3_t j, k;

	vec3_cross(n, t, b);

	for (int i = 0; i < 4; i++) {
		v = sbuf_alloc(vertex, 3);
		vn = sbuf_alloc(vertex, 3);
		vt = sbuf_alloc(vertex, 2);

		xc = i % 2;
		yc = i / 2;

		xx = xc - 0.5f;
		yy = yc - 0.5f;

		vec3_mulf(t, xx, j);
		vec3_mulf(b, yy, k);

		vec3_add(p, j, v);
		vec3_add(v, k, v);

		vec3_copy(vn, n);

		vt[0] = PX_SPRITE_W * (uv_x + xc);
		vt[1] = PX_SPRITE_H * (uv_y + yc);
	}
}

cmap_block_t c_map_blk_at(cmap_t* map, int x, int y) {
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return 0;
	
	return map->m[x + y * map->w];
}

r_mesh_t c_map_load_mesh(cmap_t* map) {
	sbuf_t index, vertex;

	vec3_t v, n, t, p;

	int q = 0;

	sbuf_init(&index, sizeof(int), 32);
	sbuf_init(&vertex, sizeof(float), 32);
	
	vec3_set(n, 0.0f, 1.0f, 0.0f);
	vec3_set(t, 1.0f, 0.0f, 0.0f);

	cmap_block_t blk;

	for (int y = 0; y < map->h; y++) {
		for (int x = 0; x < map->w; x++) {
			p[0] = x + 0.5f;
			p[1] = 0;
			p[2] = y + 0.5f;

			blk = c_map_blk_at(map, x, y);

			if (blk & C_MAP_WALL) {
				for (int i = 0; i < 4; i++) {
					n[(i + 1) % 2 * 2] = 0;
					n[(i % 2) * 2] = (i / 2) * 2 - 1;

					if (c_map_blk_at(map, x + n[0], y + n[2]) & C_MAP_WALL)
						continue;

					vec3_mulf(n, 0.5f, v);

					vec3_add(v, p, v);

					vec3_set(t, 0.0f, 1.0f, 0.0f);

					q++;
					c_map_push_wall(&vertex, v, n, t, 1, 1);
				}

				vec3_set(n, 0.0f, 1.0f, 0.0f);
				vec3_set(t, 1.0f, 0.0f, 0.0f);

				p[1] = 1;
			}

			if (blk & C_MAP_FLOOR) {
				q++;
				c_map_push_wall(&vertex, p, n, t, 0, 1);
			}
		}
	}

	int* id;

	for (int i = 0; i < q; i++) {
		int a = i * 4;

		id = sbuf_alloc(&index, 6);
		
		for (int j = 0; j < 6; j++) {
			int b = j % 3 + j / 3;

			id[j] = a + b;
		}
	}

	r_mesh_t mesh = r_add_mesh(vertex.b, q * 4, index.b, q * 6);
	
	sbuf_free(&index);
	sbuf_free(&vertex);
	
	return mesh;
}

void c_map_init(cmap_t* map, gscene_t* scene, grender_t* render, gphys_t* phys,
					unsigned char* pixels, int w, int h) {
	int col;

	int r, g, b;
	
	map->m = hunk_alloc(&scene->hunk, w * h);

	map->w = w;
	map->h = h;

	for (int i = 0; i < w * h; i++) {
		r = pixels[i * 4 + 0];
		g = pixels[i * 4 + 1];
		b = pixels[i * 4 + 2];
		
		col = r << 16 | g << 8 | b;

		switch (col) {
			case 0xffffff:
				map->m[i] = C_MAP_FLOOR;
				break;
			
			case 0xff0000:
				map->m[i] = C_MAP_WALL | C_MAP_SOLID;
				break;
			
			default:
				map->m[i] = 0;
				break;
		}
	}

	vec3_t v = {0, 0, 0};

	map->entity = g_scene_add_entity(scene);
		
		g_render_add(render, map->entity, c_map_load_mesh(map));
		
		g_phys_add_collider(phys, c_phys_map_init(v, map->m, w, h, C_MAP_SOLID));

		g_phys_add_collider(phys, c_phys_ground_init(map->m, C_MAP_FLOOR, w, h, 0.0f));
}