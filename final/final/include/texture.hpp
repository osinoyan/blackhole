#ifndef TEXTUREH
#define TEXTUREH

#include "vec3.hpp"

class texture {
	public:
		virtual vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const = 0;
};

class image_texture : public texture {
	public:
		image_texture(const char *filepath, const char *skypath);
		vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const override;
		~image_texture() { 
			delete data;
			delete data2;
		}

	private:
		unsigned char *data;				// variable to store colors of image, feel free to change its type
		int width, height, channel; // variables to store metadata of image
		unsigned char *data2;				// variable to store colors of image, feel free to change its type
		int width2, height2, channel2; // variables to store metadata of image
};

class constant_texture : public texture {
	public:
		constant_texture(const vec3& a): color(a) {}
		vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const override;
	private:
		vec3 color;		
};

#endif // !1