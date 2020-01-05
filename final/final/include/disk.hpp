#include "hitable.hpp"

class disk: public hitable {
    public:
        disk() {}
        disk(float ri, float ro, material *mat) : radius_in(ri), radius_out(ro), mat_ptr(mat) {};
        ~disk() { delete mat_ptr; }
        
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

        // disk center is fixed at (0, 0, 0), and on the y=0 plane
        float radius_in;
        float radius_out;
        material* mat_ptr;		
};
