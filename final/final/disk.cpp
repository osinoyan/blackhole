#include "disk.hpp"
#define PI 3.14159265

bool disk::hit(const ray& r, float t_min, float t_max, hit_record& rec) const { 

	// write something here ..
    vec3 A = r.origin();
    vec3 B = r.direction();
    // point on y=0 plane
    float t;
    float thick = 0.001;
    vec3 p;
    if (B.y() > thick || B.y() < -thick)
    {
        t = -A.y() / B.y();
        p = r.point_at_parameter(t);

        if (
            t > t_min && t < t_max 
            && p.squared_length() <= radius_out * radius_out 
            && p.squared_length() >= radius_in * radius_in)
        {
            // t2 is closer
            rec.t = t;
            rec.p = p;
            rec.mat_ptr = mat_ptr;

            // calculate uv
            // vec3 s_point = rec.normal;
            // float new_u = atan2(s_point.z(), s_point.x()) / (2.0 * PI) + 0.5;
            // float new_v = asin(s_point.y()) / PI + 0.5;
            // if (new_u >= 1.0)
            //     new_u = 0.999999;
            // if (new_v >= 1.0)
            //     new_v = 0.999999;
            // rec.u = new_u;
            // rec.v = new_v;
            return true;
        }
    } else {
        t = -dot(A, B) / B.squared_length();
        p = r.point_at_parameter(t);
        if (p.squared_length() > radius_out * radius_out)
            return false;
        if(t <= t_min || t >= t_max)
            return false;
        if (p.squared_length() < radius_in * radius_in)
            {
                rec.t = 0;
                rec.p = r.point_at_parameter(t);
                rec.mat_ptr = mat_ptr;
                return true;
        }
        float f_a = B.squared_length();
        float f_b = 2.0 * dot(A, B);
        float f_c = B.squared_length() - radius_out * radius_out;
        float f_d = f_b * f_b - 4.0 * f_a * f_c;
        if (f_d > 0)
        {
            float t1 = (-f_b + sqrt(f_d)) / (2.0 * f_a);
            float t2 = (-f_b - sqrt(f_d)) / (2.0 * f_a);
            if (t2 < t_max && t2 > t_min)
            {
                // t2 is closer
                rec.t = t2;
                rec.p = r.point_at_parameter(t2);
                rec.mat_ptr = mat_ptr;

                // calculate uv
                // vec3 s_point = rec.normal;
                // float new_u = atan2(s_point.z(), s_point.x()) / (2.0 * PI) + 0.5;
                // float new_v = asin(s_point.y()) / PI + 0.5;
                // if (new_u >= 1.0)
                //     new_u = 0.999999;
                // if (new_v >= 1.0)
                //     new_v = 0.999999;
                // rec.u = new_u;
                // rec.v = new_v;
                return true;
            }
        }
    }


     
    return false;
}