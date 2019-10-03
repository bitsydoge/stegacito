#ifndef COMMON_H
#define COMMON_H
#include "basictype.h"

// Pixel = 3 bytes      <--- Data 1 byte
// |rrrrr000|ggggg111|bbbbbb22|  <-----  data |22111000|
RGB Encode(RGB base, Byte data);

// |rrrrr000|ggggg111|bbbbbb22|  ---->  data |22111000|
Byte Decode(RGB encoded);
#endif // COMMON_H