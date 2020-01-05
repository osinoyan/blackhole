#include "sphere.hpp"
#define PI 3.14159265

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const { 

	// write something here ...
    float f_a = dot(r.direction(), r.direction());
    float f_b = 2.0 * dot(r.direction(), (r.origin() - center));
    float f_c = dot((r.origin() - center), (r.origin() - center)) - radius * radius;
    float f_d = f_b * f_b - 4.0 * f_a * f_c;
    if(f_d > 0)
    {
        float t1 = (-f_b + sqrt(f_d)) / (2.0 * f_a);
        float t2 = (-f_b - sqrt(f_d)) / (2.0 * f_a);
        if (t2 < t_max && t2 > t_min)
        {
            // t2 is closer
            rec.t = t2;
            rec.p = r.point_at_parameter(t2);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;

            // calculate uv
            vec3 s_point = rec.normal;
            float new_u = atan2(s_point.z(), s_point.x()) / (2.0 * PI) + 0.5;
            float new_v = asin(s_point.y()) / PI + 0.5;
            if (new_u >= 1.0) new_u = 0.999999;
            if (new_v >= 1.0) new_v = 0.999999;
            rec.u = new_u;
            rec.v = new_v;
            return true;
        }
        if (t1 < t_max && t1 > t_min)
        {

            rec.t = t1;
            rec.p = r.point_at_parameter(t1);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;

            // calculate uv
            vec3 s_point = rec.normal;
            float new_u = atan2(s_point.z(), s_point.x()) / (2.0 * PI) + 0.5;
            float new_v = asin(s_point.y()) / PI + 0.5;
            if (new_u >= 1.0) new_u = 0.999999;
            if (new_v >= 1.0) new_v = 0.999999;
            rec.u = new_u;
            rec.v = new_v;
            return true;
        }
    }
    return false;
}