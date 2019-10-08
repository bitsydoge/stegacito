// Pixel = 3 bytes      <--- Data 1 byte
// |rrrrr000|ggggg111|bbbbbb22|  <-----  data |22111000|
#include "stg_basictype.h"
#include "stg_bitmask.h"

RGB Encode(const RGB base, const Byte data)
{
	const Bitmask bitmask = GetBitmask();
	RGB encoded = { 0,0,0 };
	encoded.r = (data & bitmask.mask_data_r) | (base.r & ~bitmask.mask_pixel_r_g);
	encoded.g = (data & bitmask.mask_data_g) >> 3 | (base.g & ~bitmask.mask_pixel_r_g);
	encoded.b = (data & bitmask.mask_data_b) >> 6 | (base.b & ~bitmask.mask_pixel_b);
	return encoded;
}

// |rrrrr000|ggggg111|bbbbbb22|  ---->  data |22111000|
Byte Decode(const RGB encoded)
{
	const Bitmask bitmask = GetBitmask();
	return (Byte)(
		(encoded.r & bitmask.mask_pixel_r_g) |
		(encoded.g & bitmask.mask_pixel_r_g) << 3 |
		(encoded.b & bitmask.mask_pixel_b) << 6
		);
}