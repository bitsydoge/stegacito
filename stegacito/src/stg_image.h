#ifndef IMAGE_H
#define IMAGE_H

#include "stg_basictype.h"
#include <stddef.h>

struct Image
{
	Byte* pixel_array;
	int width, height, channels;

}; typedef struct Image Image;

Image* ImageLoad(const char* path_to_file);
void ImageDestroy(Image** to_destroy);
RGB ImageGetPixelRGB(Image* img, size_t position);
void ImageSetPixelRGB(Image* img, size_t position, RGB pixel);
void ImageSaveToPNG(Image* img, const char* path);

#endif // IMAGE_H