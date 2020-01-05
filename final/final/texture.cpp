#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

image_texture::image_texture(const char *filepath, const char *skypath)
{
	// write something here ...
	data = stbi_load(filepath, &width, &height, &channel, 0);
	data2 = stbi_load(skypath, &width2, &height2, &channel2, 0);
	// Hint: load image to variable "data"
}

vec3 image_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
	// write something here ...
	if (_hit_point.x() == -1 && _hit_point.y() == -1 && _hit_point.z() == -1)
	{
		int u = (int)(height2 * _u);
		int v = (int)(width2 * _v);
		float r = (float)(data2[channel2 * (u * width2 + v) + 0]) / 255.99;
		float g = (float)(data2[channel2 * (u * width2 + v) + 1]) / 255.99;
		float b = (float)(data2[channel2 * (u * width2 + v) + 2]) / 255.99;
		return vec3(r, g, b);
	}

	int u = (int)(height * _u);
	int v = (int)(width * _v);
	float r = (float)(data[channel * (u * width + v) + 0]) / 255.99;
	float g = (float)(data[channel * (u * width + v) + 1]) / 255.99;
	float b = (float)(data[channel * (u * width + v) + 2]) / 255.99;
	return vec3(r, g, b);
}

vec3 constant_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
	return color;
}