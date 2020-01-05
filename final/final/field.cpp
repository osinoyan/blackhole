#include "field.hpp"
#include "sphere.hpp"
#define PI 3.14159265

inline vec3 dp(float t, vec3 p, vec3 udir, vec3& kv)
{
    vec3 upo = unit_vector(-p);      // normal(p - o)
    float slpo = p.squared_length(); // squared length of (p - o)
    vec3 po_over_po3 = upo / slpo;
    kv = po_over_po3;
    return udir + t * 0.5 * po_over_po3;
}

inline vec3 RK4_position(vec3 p0, vec3 udir, float dt, vec3& v1)
{
    // Runge-Kutta 4 method
    vec3 kv1, kv2, kv3, kv4;
    vec3 kp1 = dt * dp(0, p0, udir, kv1);
    vec3 kp2 = dt * dp(0.5 * dt, p0 + 0.5 * kp1, udir, kv2);
    vec3 kp3 = dt * dp(0.5 * dt, p0 + 0.5 * kp2, udir, kv3);
    vec3 kp4 = dt * dp(dt, p0 + kp3, udir, kv4);
    vec3 p1 = p0 + (kp1 + 2.0 * kp2 + 2.0 * kp3 + kp4) / 6.0;
    v1 = udir + (kv1 + 2.0 * kv2 + 2.0 * kv3 + kv4) / 6.0;
    return p1;
}

bool field::black_hole_gravitation(vec3 p0, vec3 udir, hit_record& rec, float t_min, float dt) const {

    float ri2 = ri * ri;
    float ro2 = ro * ro;
    while (1)
    {
        float slpo = p0.squared_length(); // squared length of (p - o)
        if (slpo < 1.2)
        {
            // get into the black hole
            break;
        }
        if (slpo > squared_radius)
        {
            // get out of the field
            // calculate uv
            float new_v = atan2(udir.z(), udir.x()) / (2.0 * PI) + 0.5;
            float new_u = asin(udir.y()) / PI + 0.5;
            if (new_u >= 1.0)
                new_u = 0.999999;
            if (new_v >= 1.0)
                new_v = 0.999999;
            if (new_u < 0.0)
                new_u = 0.0;
            if (new_v < 0.0)
                new_v = 0.0;
            rec.u = new_u;
            rec.v = new_v;
            rec.p = vec3(-1, -1, -1);
            rec.mat_ptr = mat_ptr;
            return true;
            break;
        }
        // photon position after 1/c second
        vec3 v1_over_c;
        vec3 p1 = RK4_position(p0, udir, dt, v1_over_c);

        // photon go through y=0 plane
        //   need to check if hit accretion disk
        if (p0.y() * p1.y() <= t_min)
        {
            float dt = 0.5;
            while (dt > t_min && (p1.y() > t_min || p1.y() < -t_min))
            {
                vec3 v1_over_c;
                vec3 p1 = RK4_position(p0, udir, dt, v1_over_c);
                if (p0.y() * p1.y() <= t_min)
                {
                    // step too far
                    dt = dt / 2.0;
                }
                else
                {
                    // step too small
                    p0 = p1;
                    udir = unit_vector(v1_over_c);
                    dt = dt / 2.0;
                }
            }
            // on the disk with r=3~6
            slpo = p0.squared_length();
            if (slpo > ri2 && slpo < ro2)
            {
                rec.p = p0;
                rec.mat_ptr = mat_ptr;
                // calculate uv
                float new_v = atan2(p0.z(), p0.x()) / (2.0 * PI) + 0.5;                   // range[0, 1)
                float new_u = (sqrt(p0.z() * p0.z() + p0.x() * p0.x()) - ri) / (ro - ri); // range[0, 1)
                if (new_u >= 1.0)
                    new_u = 0.999999;
                if (new_v >= 1.0)
                    new_v = 0.999999;
                if (new_u < 0.0)
                    new_u = 0.0;
                if (new_v < 0.0)
                    new_v = 0.0;
                rec.u = new_u;
                rec.v = new_v;
                return true;
            }
        }
        p0 = p1;
        udir = unit_vector(v1_over_c);
    }
    return false;
}


bool field::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

    // write something here ...
    vec3 origin = r.origin();
    vec3 dir = r.direction();
    float dt = 1.0;
    float ri2 = ri * ri;
    float ro2 = ro * ro;
    if(origin.squared_length() <= squared_radius){
        // ray origin in sphere
        vec3 p = origin;
        vec3 p0 = p;
        vec3 udir = unit_vector(dir); // normal(v)
        return black_hole_gravitation(p0, udir, rec, t_min, dt);
    }else{
        // ray origin outside sphere
        float f_a = dot(dir, dir);
        float f_b = 2.0 * dot(dir, origin);
        float f_c = dot(origin, origin) - squared_radius;
        float f_d = f_b * f_b - 4.0 * f_a * f_c;
        if(f_d > 0 && dot(-origin, dir) > 0)
        {
            // ray will get into the sphere
            float t1 = (-f_b + sqrt(f_d)) / (2.0 * f_a);
            float t2 = (-f_b - sqrt(f_d)) / (2.0 * f_a);
            if (t2 < t_max && t2 > t_min)
            {
                // t2 is closer
                vec3 p = r.point_at_parameter(t2);

                vec3 p0 = p;
                vec3 udir = unit_vector(dir); // normal(v)
                return black_hole_gravitation(p0, udir, rec, t_min, dt);
            }
        }
    }

    return false;
}