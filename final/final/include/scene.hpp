#ifndef SCENEH
#define SCENEH

#include "hitable.hpp"
#include <vector>

class scene : public hitable {
    public:
		scene() {}
		scene(std::vector<hitable*> l) : list(l) {}
		~scene() {
			for (auto el : list) {
				delete el;
			}
		}

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
		std::vector<hitable*> list;
};

#endif