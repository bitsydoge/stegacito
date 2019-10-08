#include "stg_bitmask.h"

Bitmask GetBitmask()
{
	const Bitmask bitmask = 
	{ 
		0b00000111, 
		0b00000011, 
		0b00000111, 
		0b00111000, 
		0b11000000 
	};

	return bitmask;
}