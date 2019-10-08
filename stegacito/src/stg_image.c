#include "stg_image.h"

#include "stg_header.h"

#include "external/stb_image.h"
#include "external/stb_image_write.h"

#include <stdlib.h>
#include "stg_errorcode.h"
#include "stg_verbose.h"

Image* ImageLoad(const char* path_to_file)
{
	Image* my_image = (Image*)calloc(1, sizeof(Image));
	if (my_image == NULL)
		exit(ERRORCODE_CANNOT_MALLOC_IMAGE);

	my_image->pixel_array = stbi_load(path_to_file, &my_image->width, &my_image->height, &my_image->channels, 0);
	if (my_image->pixel_array == NULL)
	{
		printf("Error in loading the image : %s\n", path_to_file);
		exit(ERRORCODE_CANNOT_LOAD_IMAGE_TO_ARRAY);
	}

	VERBOSE_ON printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", my_image->width, my_image->height, my_image->channels);
	VERBOSE_ON printf("You can load a file with a maximum size of %d bytes\n", my_image->width * my_image->height - HEADER_SIZE_IN_BYTES_32);
	return my_image;
}

void ImageDestroy(Image** to_destroy)
{
	stbi_image_free((*to_destroy)->pixel_array);
	free(*to_destroy);
	*to_destroy = NULL;
}

RGB ImageGetPixelRGB(Image* img, size_t position)
{
	RGB myPixel =
	{
		img->pixel_array[position * img->channels],
		img->pixel_array[position * img->channels + 1],
		img->pixel_array[position * img->channels + 2]
	};

	return myPixel;
}

void ImageSetPixelRGB(Image* img, size_t position, RGB pixel)
{
	img->pixel_array[position * img->channels] = pixel.r;
	img->pixel_array[position * img->channels + 1] = pixel.g;
	img->pixel_array[position * img->channels + 2] = pixel.b;

}

void ImageSaveToPNG(Image* img, const char* path)
{
	VERBOSE_ON printf("Saving the file : \"%s\" ...\n", path);
	stbi_write_png(path, img->width, img->height, img->channels, img->pixel_array, img->width * img->channels);
	printf("File \"%s\" have been saved.\n", path);
}