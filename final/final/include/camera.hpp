#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"
#include "util.hpp"

#define PI 3.14159265

class camera {
public:

	camera() {}

	// vfov: vertical field of view in degree
	camera(vec3 lookfrom, vec3 lookat, vec3 up, float vfov, float aspect) {

		origin = lookfrom;

		// write something here ...
		// pi = atan(1)*4, [vfov * pi / 180 / 2]
		height = 2 * tan(vfov * PI / 180 / 2);
		width = height * aspect;

		w_dir = unit_vector(lookfrom - lookat);
		u_dir = cross(up, w_dir);
		u_dir.make_unit_vector();
		v_dir = cross(w_dir, u_dir);
		v_dir.make_unit_vector();

		lower_left_corner = lookfrom - w_dir - (u_dir * width / 2) - (v_dir * height / 2);
		// std::cout << origin << "\n";
		// std::cout << lower_left_corner << "\n";
	}

	inline ray get_ray(float s, float t) const {

		// write something here ...
		vec3 img_point = lower_left_corner + (u_dir * width * s) + (v_dir * height * t);
		return ray(origin, img_point-origin);

		// return ray point to (s ,t, 1) for now
		// you may need to remove this line
		// return ray(origin, vec3(s, t, 1));
	}

	vec3 lower_left_corner;
	// vec3 horizontal;
	// vec3 vertical;
	vec3 origin;
	vec3 w_dir;
	vec3 u_dir;
	vec3 v_dir;
	float width;
	float height;
};

#endif
