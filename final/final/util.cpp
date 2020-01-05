#include "util.hpp"
#include "triangle.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::vector<triangle> LoadModel(const char* filepath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath);
	if (!warn.empty())
	{
		std::cout << warn << std::endl;
	}
	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}

	std::vector<triangle> list;

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++)
	{
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			size_t fv = shapes[s].mesh.num_face_vertices[f];

			vec3 vertices[3];
			vec3 texcoords[3];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++)
			{
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				// tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
				// tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
				// tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
				//tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
				//tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
				vertices[v] = vec3(vx, vy, vz);
				//texcoords[v] = vec3(tx, ty, 0);
			}

			// We assign material outside, set material to null for now
			list.push_back(triangle(vertices[0], vertices[1], vertices[2], nullptr));

			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	return list;
}

void SaveImage(const char* filepath, float *data, int image_width, int image_height, int sample) {
	
	unsigned char* image = new unsigned char[image_height * image_width * 3];
	
	for (int j = 0; j < image_height; ++j) {
		for (int i = 0; i < image_width; ++i) {
			for (int n = 0; n < 3; ++n) {
				
				// Preform MSAA
				float tempColor = (data[(j * image_width + i) * 3 + n]) / (float)(sample + 1);

				// Apply Gamma Correction and Color clamping
				tempColor = ColorCorrection(tempColor);

				// Convert Color from float [0.0, 1.0] to unsigned char [0, 255]
				image[(j * image_width + i) * 3 + n] = int(tempColor * 255.99);
			}
		}
	}

	stbi_flip_vertically_on_write(true);
	if (stbi_write_png(filepath, image_width, image_height, 3, image, 0) == 0)
	{
		std::cerr << "Error when saving image: " << filepath << "\n";
	}

	delete image;
}

float ColorCorrection(float value) {

	// Please use Gamma as 2.0 and clamp the value between [0.0, 1.0]

	// write something here ...
	float new_value = sqrt(value);
	return new_value > 1.0 ? 1.0 : new_value;
}