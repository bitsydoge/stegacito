#include "basictype.h"
#include "bitmask.h"
#include "external/argtable3.h"
#include "image.h"
#include "file.h"
#include "common.h"
#include "verbose.h"

int decoder_main(struct arg_file* image, struct arg_file* output)
{
	Bitmask bitmask = GetBitmask();

	// --------------------------------- //
	// Load Image
	Image* my_image = ImageLoad(image->filename[0]);
	VERBOSE_ON printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", my_image->width, my_image->height, my_image->channels);

	// --------------------------------- //
	// File Opening
	File* my_file;
	if(output->count>0)
	{
		my_file = FileLoad(output->filename[0], "w+");
	}
	else
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%s%s%s", image->filename[0], "_extracted", ".txt");
		my_file = FileLoad(buf, "w+");
	}
	
	for (int i = 0; i < my_image->height * my_image->width; i += my_image->channels)
	{
		const RGB pixel = { my_image->pixel_array[i], my_image->pixel_array[i + 1], my_image->pixel_array[i + 2] };
		Byte data_extracted = Decode(pixel);
		fwrite(&data_extracted, sizeof(Byte), 1, my_file->file_handler);
		VERBOSE_ON printf("Pixel %d (%d,%d,%d) : %d \n", i / 4, my_image->pixel_array[i], my_image->pixel_array[i + 1], my_image->pixel_array[i + 2], data_extracted);
	}

	//Clean
	VERBOSE_ON printf("\n");
	ImageDestroy(&my_image);
	FileUnload(&my_file);
	return 0;
}
