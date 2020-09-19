#ifndef C_PHYS_PLANE_H
#define C_PHYS_PLANE_H

#include "c_phys_collider.h"

cphys_collider_t		c_phys_plane_init(vec3_t n, float d);

void					c_phys_plane_move(cphys_collider_t* c, vec3_t v);

void					c_phys_collide_plane_aabb(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_plane_plane(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_plane_capsule(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

#endif
