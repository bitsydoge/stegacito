#include "header.h"
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "common.h"
#include "verbose.h"
#include <stdlib.h>
#include "errorcode.h"

Header HeaderCreate(HEADER_FILE_SIZE_CONTAINER_TYPE_32 file_size, const char* filename)
{
	Header header_contrainer = { 0 };
	// Control Key // THE KEY SHOULD NEVER CHANGE !!
	header_contrainer.header[0] = HEADER_CONTROL_KEY_1;
	header_contrainer.header[1] = HEADER_CONTROL_KEY_2;
	header_contrainer.header[2] = HEADER_CONTROL_KEY_3;
	header_contrainer.header[3] = HEADER_CONTROL_KEY_4;
	header_contrainer.header[4] = HEADER_CONTROL_KEY_5;

	// Version
	header_contrainer.header[5] = GetVersionNumber();

	// Size
	HEADER_FILE_SIZE_CONTAINER_TYPE_32 * file_size_in_header = (HEADER_FILE_SIZE_CONTAINER_TYPE_32*)&header_contrainer.header[6];
	*file_size_in_header = file_size;

	// Name
	strncpy((char *)&header_contrainer.header[10], filename, HEADER_FILE_NAME_CHAR_MAX);

	// Data
	// Data should start at [10]

	return header_contrainer;
}

Header HeaderExtract(Image * my_image)
{
	Header my_header = { 0 };
	for(HEADER_FILE_SIZE_CONTAINER_TYPE_32 i = 0; i < HEADER_SIZE_IN_BYTES_32; i++)
	{
		const RGB pixel = ImageGetPixelRGB(my_image, i);
		my_header.header[i] = Decode(pixel);
	}

	// Check Control Key
	if
	(
		my_header.header[0] == HEADER_CONTROL_KEY_1 && 
		my_header.header[1] == HEADER_CONTROL_KEY_2 && 
		my_header.header[2] == HEADER_CONTROL_KEY_3 && 
		my_header.header[3] == HEADER_CONTROL_KEY_4 && 
		my_header.header[4] == HEADER_CONTROL_KEY_5
	)
	{
		VERBOSE_ON printf("Header extracted is a good header\n");
	}
	else
	{
		printf("Error ! The Image is probably not steganographied !\n");
		exit(ERRORCODE_HEADER_IS_NOT_A_STEGACITO_ONE);
	}

	return my_header;
}

