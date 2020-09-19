#ifndef C_PHYS_CAPSULE_H
#define C_PHYS_CAPSULE_H

#include "c_phys_collider.h"

cphys_collider_t		c_phys_capsule_init(vec3_t p, float h, float r);

void					c_phys_capsule_move(cphys_collider_t* c, vec3_t v);

void					c_phys_collide_capsule_aabb(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_capsule_plane(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

void					c_phys_collide_capsule_capsule(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b);

#endif
