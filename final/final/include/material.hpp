#ifndef MATERIALH
#define MATERIALH

#include "ray.hpp"
#include "hitable.hpp"
#include "texture.hpp"

class material {
    public:
        virtual bool scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
				virtual vec3 emitted() const;
				virtual vec3 accretion(hit_record &rec) const;
};

class lambertian : public material {
    public:
		// lambertian with texture
        lambertian(texture* tex) : tex_ptr(tex) {}
		// lambertian with color only
		lambertian(const vec3& a) :tex_ptr(new constant_texture(a)) {}
		
		~lambertian() { delete tex_ptr; }
		
		virtual bool scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const override;

		texture* tex_ptr;
};

class metal : public material {
    public:
        metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}
		virtual bool scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const override;

        vec3 albedo;
        float fuzz;
};

class dielectric : public material {
	public:
		dielectric(float ri) : ref_idx(ri) {}
		virtual bool scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const override;

		float ref_idx;
};

class light : public material {
	public:
		light(const vec3& c) : emit(c) {}
		virtual bool scatter(const ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const override;
		virtual vec3 emitted() const override;

		vec3 emit;
};

class gravitation : public material {
	public:
		// with texture
   	gravitation(texture* tex) : tex_ptr(tex) {}
		// with color only
		gravitation(const vec3 &c) : tex_ptr(new constant_texture(c)) {}
		virtual bool scatter(const ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const override;
		vec3 accretion(hit_record &rec) const override;

		// disk color
		vec3 emit;
		texture *tex_ptr;
};

#endif