#ifndef TRANSFORMH
#define TRANSFORMH

#include "hitable.hpp"

class transform : public hitable
{
	public:
		transform(hitable *_target, const vec3& _displacement, const vec3& _rotateAxis, const float _rotateAngle)
			: target(_target), displacement(_displacement), rotateAxis(_rotateAxis), rotateAngle(_rotateAngle) {}

		~transform() {
			delete target;
		}

		bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

		hitable *target; // target we want to transform
		
		vec3 displacement; // translate
		
		vec3 rotateAxis; // rotate
		float rotateAngle;
};

#endif
