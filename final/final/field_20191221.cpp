#include "field.hpp"
#define PI 3.14159265

bool field::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

    // write something here ...
    vec3 origin = r.origin();
    vec3 dir = r.direction();
    if(origin.squared_length() <= squared_radius){
        // ray origin in sphere
        // std::cout << "YEEEEray origin in sphereEEEEEEEEEEEE\n";
        vec3 p = origin;
        vec3 p0 = p;
        vec3 udir = unit_vector(dir); // normal(v)
        vec3 upo = unit_vector(-p0);  // normal(p - o)
        while (1)
        {
            float slpo = p0.squared_length(); // squared length of (p - o)
            if (slpo < 0.98 || slpo > squared_radius)
            {
                // get into the black hole or get out of the field
                break;
            }
            // photon position after 1/c second
            vec3 po_over_po3 = upo / slpo;
            vec3 p1 = p0 + udir + po_over_po3 / 4.0;
            vec3 v1_over_c = udir + po_over_po3 / 2.0;

            // photon go through y=0 plane
            if (p0.y() * p1.y() <= t_min)
            {
                float dt = 0.5;
                while (dt > t_min && (p1.y() > t_min || p1.y() < -t_min))
                {
                    vec3 po_over_po3 = upo / slpo;
                    vec3 p1 = p0 + dt * udir + dt * dt * po_over_po3 / 4.0;
                    if (p0.y() * p1.y() <= t_min)
                    {
                        // step too far
                        dt = dt / 2.0;
                    }
                    else
                    {
                        // step too small
                        p0 = p1;
                        vec3 v1_over_c = udir + dt * po_over_po3 / 2.0;
                        udir = unit_vector(v1_over_c);
                        upo = unit_vector(-p0);
                        dt = dt / 2.0;
                    }
                }
                // on the disk with r=3~6
                slpo = p0.squared_length();
                if (slpo > 9.0 && slpo < 36.0)
                {
                    // std::cout << "\n";
                    // std::cout << "\n";
                    // std::cout << "HUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n";
                    // std::cout << "[p0 =" << p0 << "]";
                    // std::cout << "[p1 =" << p1 << "]";
                    // std::cout << "[v1_over_c =" << v1_over_c << "]";
                    // std::cout << "\n";
                    // std::cout << "\n";
                    // std::cout << "\n";
                    rec.p = p0;
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }

            p0 = p1;
            udir = unit_vector(v1_over_c);
            upo = unit_vector(-p0);
        }
    }else{
        // ray origin outside sphere
        // std::cout << "YEEEEray origin outside sphereEEEEEEEEEEEE\n";
        float f_a = dot(dir, dir);
        float f_b = 2.0 * dot(dir, origin);
        float f_c = dot(origin, origin) - squared_radius;
        float f_d = f_b * f_b - 4.0 * f_a * f_c;
        if(f_d > 0 && dot(-origin, dir) > 0)
        {
            // ray will get into the sphere
            // std::cout << "YEEEEray will get into the sphereEEEEEEEEEEEE\n";
            float t1 = (-f_b + sqrt(f_d)) / (2.0 * f_a);
            float t2 = (-f_b - sqrt(f_d)) / (2.0 * f_a);
            if (t2 < t_max && t2 > t_min)
            {
                // t2 is closer
                vec3 p = r.point_at_parameter(t2);

                vec3 p0 = p;
                vec3 udir = unit_vector(dir); // normal(v)
                vec3 upo = unit_vector(-p0); // normal(p - o)
                while(1){
                    float slpo = p0.squared_length(); // squared length of (p - o)
                    if (slpo < 0.001 || slpo > squared_radius)
                    {
                        // get into the black hole or get out of the field
                        break;
                    }
                    if (slpo > 0.001 && slpo < 0.1)
                    {
                        int a = 1;
                    }
                    // photon position after 1/c second
                    vec3 po_over_po3 = upo / slpo;
                    vec3 p1 = p0 + udir + po_over_po3 / 4.0;
                    vec3 v1_over_c = udir + po_over_po3 / 2.0;
                    
                    // photon go through y=0 plane
                    if (p0.y() * p1.y() <= t_min) {
                        float dt = 0.5;
                        while( dt > t_min && (p1.y() > t_min || p1.y() < -t_min) ){
                            vec3 po_over_po3 = upo / slpo;
                            vec3 p1 = p0 + dt * udir + dt * dt * po_over_po3 / 4.0;
                            if (p0.y() * p1.y() <= t_min){
                                // step too far
                                dt = dt / 2.0;
                            } else {
                                // step too small
                                p0 = p1;
                                vec3 v1_over_c = udir + dt * po_over_po3 / 2.0;
                                udir = unit_vector(v1_over_c);
                                upo = unit_vector(-p0);
                                dt = dt / 2.0;
                            }
                        }
                        // on the disk with r=3~6
                        slpo = p0.squared_length();
                        if (slpo > 9.0 && slpo < 36.0) {
                            // std::cout << "\n";
                            // std::cout << "\n";
                            // std::cout << "HUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n";
                            // std::cout << "[p0 =" << p0 << "]";
                            // std::cout << "[p1 =" << p1 << "]";
                            // std::cout << "[v1_over_c =" << v1_over_c << "]";
                            // std::cout << "\n";
                            // std::cout << "\n";
                            // std::cout << "\n";
                            rec.p = p0;
                            rec.mat_ptr = mat_ptr;
                            return true;
                        }
                    }



                    p0 = p1;
                    udir = unit_vector(v1_over_c);
                    upo = unit_vector(-p0);
                }

                // std::cout << "---------------------------------\n";

                // rec.t = t2;
                // rec.p = r.point_at_parameter(t2);
                // rec.normal = (rec.p - center) / radius;
                // rec.mat_ptr = mat_ptr;

                // // calculate uv
                // vec3 s_point = rec.normal;
                // float new_u = atan2(s_point.z(), s_point.x()) / (2.0 * PI) + 0.5;
                // float new_v = asin(s_point.y()) / PI + 0.5;
                // if (new_u >= 1.0) new_u = 0.999999;
                // if (new_v >= 1.0) new_v = 0.999999;
                // rec.u = new_u;
                // rec.v = new_v;
            }
        }
    }

    return false;
}