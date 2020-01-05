#ifndef UTILH
#define UTILH

#include <vector>

#include "triangle.hpp"
#include "hitable.hpp"
#include "vec3.hpp"

std::vector<triangle> LoadModel(const char*);

void SaveImage(const char* filepath,float *data, int image_width, int image_height, int sample);

float ColorCorrection(float value);

#endif