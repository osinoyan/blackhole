#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.hpp"

class triangle : public hitable
{
public:
	// we can extend it to hold normal and texture coordinate information later
	triangle(const vec3& _v0, const vec3& _v1, const vec3& _v2, material* _material)
		: v0(_v0), v1(_v1), v2(_v2), triangle_mat(_material)
	{
		normal = unit_vector(cross(v1 - v0, v2 - v0));
	}

	~triangle() {
		if (triangle_mat != nullptr) {
			delete triangle_mat;
			triangle_mat = nullptr;
		}
	}

	virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;

	vec3 v0, v1, v2; // vertex
	vec3 normal;
	material* triangle_mat;
};

#endif
