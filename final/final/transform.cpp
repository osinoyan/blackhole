#include "transform.hpp"
#define PI 3.14159265

inline vec3 Translate(vec3 target, vec3 displacement) {
	
	// write something here ...
	return target + displacement;
}

vec3 Rotate(vec3 target, vec3 axis, float angle) {

	// write something here ...
	if ( (angle == 180 || angle == -180) && axis.x() == 0 && axis.y() == 1 && axis.z() == 0)
	{
		return vec3(-target.x(), target.y(), -target.z());
	}

	vec3 u = unit_vector(axis);
	float angle_arc = angle * PI / 180;
	float coss = cos(angle_arc);
	float sinn = sin(angle_arc);
	float one_minus_coss = (1 - coss);
	float uxyomc = u.x() * u.y() * one_minus_coss;
	float uxzomc = u.x() * u.z() * one_minus_coss;
	float uzyomc = u.z() * u.y() * one_minus_coss;
	float uxsin = u.x() * sinn;
	float uysin = u.y() * sinn;
	float uzsin = u.z() * sinn;
	float tmd[9] = {
			coss + u.x() * u.x() * one_minus_coss,
			uxyomc - uzsin,
			uxzomc + uysin,
			uxyomc + uzsin,
			coss + u.y() * u.y() * one_minus_coss,
			uzyomc - uxsin,
			uxzomc - uysin,
			uzyomc + uxsin,
			coss + u.z() * u.z() * one_minus_coss};

	float new_x = tmd[0] * target.x() + tmd[1] * target.y() + tmd[2] * target.z();
	float new_y = tmd[3] * target.x() + tmd[4] * target.y() + tmd[5] * target.z();
	float new_z = tmd[6] * target.x() + tmd[7] * target.y() + tmd[8] * target.z();

	// vec3 result = vec3(new_x, new_y, new_z);
	// std::cout << "==========================[" << angle << "]"
	// 					<< "\n";
	// std::cout << "[coss = " << coss << "]"
	// 					<< "[sinn = " << sinn << "]"
	// 					<< "[1-coss = " << one_minus_coss << "]"
	// 					<< "[0 = " << tmd[0] << "]"
	// 					<< "[1 = " << tmd[1] << "]"
	// 					<< "[2 = " << tmd[2] << "]"
	// 					<< "[3 = " << tmd[3] << "]"
	// 					<< "[4 = " << tmd[4] << "]"
	// 					<< "[5 = " << tmd[5] << "]"
	// 					<< "[6 = " << tmd[6] << "]"
	// 					<< "[7 = " << tmd[7] << "]"
	// 					<< "[8 = " << tmd[8] << "]"
	// 					<< "\n";
	// std::cout << "(" << target << ")"
	// 					<< " -------> "
	// 					<< "(" << result << ")"
	// 					<< "\n";

	return vec3(new_x, new_y, new_z);
}

bool transform::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	// // write something here ...
	vec3 origin = r.origin();
	vec3 dir = r.direction();
	origin = Translate(origin, -displacement);
	if ((rotateAngle == 180 || rotateAngle == -180) && rotateAxis.x() == 0 && rotateAxis.y() == 1 && rotateAxis.z() == 0){
		origin = vec3(-origin.x(), origin.y(), -origin.z());
		dir = vec3(-dir.x(), dir.y(), -dir.z());
	}else	if (rotateAngle != 0.0){
		origin = Rotate(origin, rotateAxis, -rotateAngle);
		dir = Rotate(dir, rotateAxis, -rotateAngle);
	}
	ray new_ray = ray(origin, dir);

	bool hit = target->hit(new_ray, t_min, t_max, rec);
	
	if (hit){
		if ((rotateAngle == 180 || rotateAngle == -180) && rotateAxis.x() == 0 && rotateAxis.y() == 1 && rotateAxis.z() == 0){
			rec.p = vec3(-rec.p.x(), rec.p.y(), -rec.p.z());
			rec.normal = vec3(-rec.normal.x(), rec.normal.y(), -rec.normal.z());
		} else if (rotateAngle != 0.0){
			rec.p = Rotate(rec.p, rotateAxis, rotateAngle);
			rec.normal = Rotate(rec.normal, rotateAxis, rotateAngle);
		}
		rec.p = Translate(rec.p, displacement);
		return true;
	}
	return false;
}