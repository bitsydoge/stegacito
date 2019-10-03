#include "encoder.h"

#include <stdio.h>
#include <stdlib.h>

#include "verbose.h"
#include "errorcode.h"
#include "image.h"
#include "header.h"
#include "file.h"
#include "common.h"

int encoder_main(struct arg_file * file, struct arg_file * image, struct arg_file * output)
{
	// --------------------------------- //
	// Load Image
	Image* my_image = ImageLoad(image->filename[0]);

	// --------------------------------- //
	// Load File
	File* my_file = FileLoad(file->filename[0], "rb+");

	Header my_header = HeaderCreate(my_file->size, file->basename[0]);

	// --------------------------------- //
	// Check if it can be added in Image
	if (my_file->size <= my_image->width*my_image->height - HEADER_SIZE_IN_BYTES_32)
	{
		VERBOSE_ON printf("The file can be hidden in the image\n");
	}
	else
	{
		printf("Error, the file can't be hidden in the image, it is too heavy\n");
		exit(3);
	}
	// --------------------------------- //
	// Insert Header
	VERBOSE_ON printf("Header Encoding ...\n");
	for(HEADER_FILE_SIZE_CONTAINER_TYPE_32 i = 0; i < HEADER_SIZE_IN_BYTES_32; i++)
	{
		// Get Pixel
		const RGB pixel_original = ImageGetPixelRGB(my_image, i);
		VERBOSE_ON printf("Original Pixel = (%d,%d,%d)\n", pixel_original.r, pixel_original.g, pixel_original.b);
	
		// Encode Pixel
		const RGB pixel_encoded = Encode(pixel_original, my_header.header[i]);

		// Insert in Image Array
		ImageSetPixelRGB(my_image, i, pixel_encoded);
	}
	//fseek(my_file->file_handler, 0L, SEEK_SET);
	// --------------------------------- //
	// Pixel Encoding
	VERBOSE_ON printf("Pixel Encoding ...\n");
	int error_counter = 0;
	for (HEADER_FILE_SIZE_CONTAINER_TYPE_32 i = HEADER_SIZE_IN_BYTES_32; i < my_file->size + HEADER_SIZE_IN_BYTES_32; i++)
	{
		VERBOSE_ON printf("-------------------\n");
		VERBOSE_ON printf("Pixel Number : %d\n", i - HEADER_SIZE_IN_BYTES_32);

		// ------------------------------------- //
		// Get Values
		//const Byte data = fgetc(my_file->file_handler);
		Byte data = 0; 
		fread(&data, sizeof(Byte), 1, my_file->file_handler);
		VERBOSE_ON printf("Original Data = \"%d\"\n", data);
		const RGB pixel_original = ImageGetPixelRGB(my_image, i);
		VERBOSE_ON printf("Original Pixel = (%d,%d,%d)\n", pixel_original.r, pixel_original.g, pixel_original.b);

		// ------------------------------------- //
		// Encode Data in Pixel and Save it in image Array
		const RGB pixel_encoded = Encode(pixel_original, data);
		VERBOSE_ON printf("Encoded Pixel = (%d,%d,%d)\n", pixel_encoded.r, pixel_encoded.g, pixel_encoded.b);
		ImageSetPixelRGB(my_image, i, pixel_encoded);

		// ------------------------------------- //
		// Check if the decode is working
		const Byte data_extract = Decode(pixel_encoded);
		if (data_extract != data)
			error_counter++;
		VERBOSE_ON printf("Checking Decoding : %s\n", data_extract == data ? "OK" : "ERROR");
	}

	// Error Check
	VERBOSE_ON printf("\n-------------------\n");
	if (error_counter != 0)
	{
		exit(ERRORCODE_ERROR_IN_ENCODING);
	}	
	VERBOSE_ON printf("Aucune Erreur d'encodage.\n");

	// Image Save
	if(output->count > 0)
	{
		ImageSaveToPNG(my_image, output->filename[0]);
	}
	else
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%s%s", "stegacito_", image->basename[0]);
		ImageSaveToPNG(my_image, buf);
	}
	

	//Clean
	VERBOSE_ON printf("\n");
	ImageDestroy(&my_image);
	FileUnload(&my_file);
	return 0;
}
