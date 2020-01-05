#include "triangle.hpp"

bool triangle::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
	// write something here ...
	vec3 orig = _ray.origin();
	vec3 dir = _ray.direction();

	vec3 v0v1 = v1 - v0;
	vec3 v0v2 = v2 - v0;
	vec3 pvec = cross(dir, v0v2);
	float det = dot(v0v1, pvec);

	// CULLING
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < t_min) return false;
	float invDet = 1 / det;

	vec3 tvec = orig - v0;
	float u, v, t;
	u = dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1)
		return false;

	vec3 qvec = cross(tvec, v0v1);
	v = dot(dir, qvec) * invDet;
	if (v < 0 || u + v > 1)
		return false;

	t = dot(v0v2, qvec) * invDet;

	rec.t = t;
	rec.p = _ray.point_at_parameter(t);
	rec.normal = normal;
	rec.mat_ptr = triangle_mat;
	return true;
}