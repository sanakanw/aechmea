#ifndef C_PHYS_AABB_H
#define C_PHYS_AABB_H

#include "c_phys_collider.h"

cphys_collider_t		c_phys_aabb_init(vec3_t a, vec3_t b);

void					c_phys_aabb_move(cphys_collider_t* c, vec3_t v);

void					c_phys_collide_aabb_aabb(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_aabb_plane(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_aabb_capsule(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

#endif
