#ifndef BITMASK_H
#define BITMASK_H

#include "stg_basictype.h"

struct Bitmask
{
	Byte mask_pixel_r_g;
	Byte mask_pixel_b;
	Byte mask_data_r; 
	Byte mask_data_g;
	Byte mask_data_b;

}; typedef struct Bitmask Bitmask;

Bitmask GetBitmask();

#endif // BITMASK_H