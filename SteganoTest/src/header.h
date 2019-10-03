#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include <limits.h>

// ------------------------------- //
// Header Constants & Types
// ------------------------------- //

// ----- File Size Container ----- //
#if defined(UINT64_MAX)
typedef uint64_t HEADER_FILE_SIZE_CONTAINER_TYPE_64;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned int HEADER_FILE_SIZE_CONTAINER_TYPE_64;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
#elif LONG_MAX = 0xFFFFFFFFFFFFFFFF
typedef unsigned long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
#elif LLONG_MAX = 0xFFFFFFFFFFFFFFFF
typedef unsigned long long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 8
#elif
typedef unsigned long HEADER_FILE_SIZE_CONTAINER_TYPE_64;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 4
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64_NOT_AVAIABLE;
#endif


#if defined(UINT32_MAX)
typedef uint32_t HEADER_FILE_SIZE_CONTAINER_TYPE_32;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 4
#elif UINT_MAX == 0xFFFFFFFF
typedef INT HEADER_FILE_SIZE_CONTAINER_TYPE_32;
#define HEADER_FILE_SIZE_CONTAINER_SIZE_64 4
#endif

// ----- File Name Container ---- //
#define HEADER_FILE_NAME_CHAR_MAX 255
#define HEADER_FILE_NAME_CHAR_TYPE unsigned char
#define HEADER_FILE_NAME_CHAR_SIZE_IN_BYTE 1

// ----- Version Container ------ //
#define HEADER_VERSION_TYPE unsigned char
#define HEADER_VERSION_SIZE 1

// ----- Flag Container --------- //
#define HEADER_FLAGS_TYPE unsigned char
#define HEADER_FLAGS_SIZE 1

#define HEADER_SIZE_IN_BYTES_64 (HEADER_FILE_SIZE_CONTAINER_SIZE_64+(HEADER_FILE_NAME_CHAR_MAX*HEADER_FILE_NAME_CHAR_SIZE_IN_BYTE)+HEADER_VERSION_SIZE+HEADER_FLAGS_SIZE)
#define HEADER_SIZE_IN_BYTES_32 (HEADER_FILE_SIZE_CONTAINER_SIZE_64+(HEADER_FILE_NAME_CHAR_MAX*HEADER_FILE_NAME_CHAR_SIZE_IN_BYTE)+HEADER_VERSION_SIZE+HEADER_FLAGS_SIZE)

// Should be 327 if a 64 bit container is used
// Should be 291 if a 32 bit container is used

#endif // HEADER_H