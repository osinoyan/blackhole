#include "material.hpp"
#include "random.hpp"

vec3 rand_in_unit_sphere(){
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while(p.squared_length() >= 1.0);
	return p;
}

vec3 rand_on_unit_sphere(){
	vec3 p;
	p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	p.make_unit_vector();
	return p;
}

vec3 reflect(const vec3 &v, const vec3 &n){
	return v - 2 * dot(v, n) * n;
}
// is it refracted
bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3& refracted){
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if(discriminant > 0){
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}else{
		return false;
	}
}

vec3 material::emitted() const
{

	// material that is not light don't returns energy

	return vec3(0, 0, 0);
}

vec3 material::accretion(hit_record &rec) const
{

	// material that is not light don't returns energy

	return vec3(0, 0, 0);
}

bool lambertian::scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {

	// write something here ...
	vec3 target = rec.p + rec.normal + rand_on_unit_sphere();
	scattered = ray(rec.p, target-rec.p);
	attenuation = tex_ptr->value_at_uv(rec.u, rec.v, rec.p);

	return true;
}

bool metal::scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {
	
	// write something here ...
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected + fuzz * rand_in_unit_sphere());
	attenuation = albedo;
	// return true;
	return (dot(scattered.direction(), rec.normal) > 0);
}

bool dielectric::scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {
    
	// write something here ...
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0, 1.0, 1.0);
	vec3 refracted;
	if (dot(r_in.direction(), rec.normal) > 0) {
		// lights go into this object
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
	} else {
		// lights come from this object
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / ref_idx;
	}
	// if NOT total internal reflection
	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
		scattered = ray(rec.p, refracted);
	} else {
		// total internal reflection
		scattered = ray(rec.p, reflected);
		return false;
	}
	return true;

}

vec3 light::emitted() const {

	// write something here ...
	return emit;
}

bool light::scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {

	// write something here ...
	return false;
}

bool gravitation::scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const
{

	// write something here ...
	return false;
}
vec3 gravitation::accretion(hit_record &rec) const
{

	// write something here ...
	return tex_ptr->value_at_uv(rec.u, rec.v, rec.p);
}