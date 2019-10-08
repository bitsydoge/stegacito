#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include <limits.h>
#include "stg_basictype.h"
#include "stg_version.h"
#include "stg_image.h"

// ------------------------------- //
// Header Constants & Types
// ------------------------------- //

// ----- File Size Container ----- //
//#if defined(UINT64_MAX)
//typedef uint64_t HEADER_FILE_SIZE_CONTAINER_TYPE_64;
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
//#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
//typedef unsigned int HEADER_FILE_SIZE_CONTAINER_TYPE_64;
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
//#elif LONG_MAX = 0xFFFFFFFFFFFFFFFF
//typedef unsigned long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
//#elif LLONG_MAX = 0xFFFFFFFFFFFFFFFF
//typedef unsigned long long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
//#elif
//typedef unsigned long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 4
//#define HEADER_FILE_SIZE_CONTAINER_SIZE_64_NOT_AVAIABLE;
//#endif


#if defined(UINT32_MAX)
typedef uint32_t HEADER_FILE_SIZE_CONTAINER_TYPE_32;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_32 4
#elif UINT_MAX == 0xFFFFFFFF
typedef INT HEADER_FILE_SIZE_CONTAINER_TYPE_32;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_32 4
#endif

// --------- Control Key --------- //
#define HEADER_CONTROL_KEY_NB_BYTES 5
#define HEADER_CONTROL_KEY_1 0b10111011
#define HEADER_CONTROL_KEY_2 0b10110101
#define HEADER_CONTROL_KEY_3 0b01100101
#define HEADER_CONTROL_KEY_4 0b10111000
#define HEADER_CONTROL_KEY_5 0b10111011

// ----- File Name Container ---- //
#define HEADER_FILE_NAME_CHAR_MAX 255
#define HEADER_FILE_NAME_CHAR_TYPE unsigned char
#define HEADER_FILE_NAME_CHAR_SIZE_IN_BYTE 1

// ----- Version Container ------ //
#define HEADER_VERSION_TYPE unsigned char
#define HEADER_VERSION_SIZE 1

#define HEADER_SIZE_IN_BYTES_32 (HEADER_FILE_SIZE_CONTAINER_SIZE_32+(HEADER_FILE_NAME_CHAR_MAX*HEADER_FILE_NAME_CHAR_SIZE_IN_BYTE)+HEADER_VERSION_SIZE+HEADER_CONTROL_KEY_NB_BYTES)

struct Header
{
	Byte header[HEADER_SIZE_IN_BYTES_32];

}; typedef struct Header Header;

Header HeaderCreate(HEADER_FILE_SIZE_CONTAINER_TYPE_32 file_size, const char * filename);
Header HeaderExtract(Image* my_image);

#endif // HEADER_H