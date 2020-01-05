#ifndef RAYH
#define RAYH

#include "vec3.hpp"

class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b; }
        vec3 origin() const { return A; }

        // note diection hasn't normalized
        vec3 direction() const { return B; }
        vec3 point_at_parameter(float t) const { return A + t * B; }

        vec3 A;
        vec3 B;
};

#endif