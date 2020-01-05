#ifndef FIELDH
#define FIELDH

#include "hitable.hpp"

class field: public hitable {
    public:
        field() {}
        field(float r, float ri, float ro, material *mat) : radius(r), ri(ri), ro(ro), squared_radius(r * r), mat_ptr(mat){};
        ~field() { delete mat_ptr; }

        bool black_hole_gravitation(vec3 p0, vec3 udir, hit_record &rec, float t_min, float dt) const;
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

        // center is fixed at (0, 0, 0)
        float radius;
        float squared_radius;
        // accretion disk
        float ri;
        float ro;
        material* mat_ptr;		
};

#endif