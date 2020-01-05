#ifndef HITABLEH
#define HITABLEH

#include "ray.hpp"

class material;

struct hit_record {
    float t; // ray length
    vec3 p; // hit point
	float u, v; // hit point's uv
    vec3 normal; // normal
    material *mat_ptr; // pointer to hit point's material
};

class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif