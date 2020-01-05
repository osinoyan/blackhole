#include "random.hpp"
#include "config.hpp"

double drand48(void)
{
	seed = (0x5DEECE66DLL * seed + 0xB16) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)0x100000000LL);
}