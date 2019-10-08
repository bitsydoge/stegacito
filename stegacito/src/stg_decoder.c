#include "stg_basictype.h"
#include "external/argtable3.h"
#include "stg_image.h"
#include "stg_file.h"
#include "stg_common.h"
#include "stg_verbose.h"

int decoder_main(struct arg_file* image, struct arg_file* output)
{
	// --------------------------------- //
	// Load Image
	Image* my_image = ImageLoad(image->filename[0]);
	VERBOSE_ON printf("Loaded image with a width of %d px, a height of %d px and %d channels\n", my_image->width, my_image->height, my_image->channels);

	Header my_header = HeaderExtract(my_image);
	const int filesize = *(HEADER_FILE_SIZE_CONTAINER_TYPE_32*)(&my_header.header[6]);

	// --------------------------------- //
	// File Opening
	File* my_file;
	char buf[512];
	if(output->count>0)
	{
		my_file = FileLoad(output->filename[0], "wb+");
	}
	else
	{
		snprintf(buf, sizeof buf, "%s%s", "extracted_", &my_header.header[10]);
		my_file = FileLoad(buf, "wb+");
	}

	for (int i = HEADER_SIZE_IN_BYTES_32*my_image->channels; i < (HEADER_SIZE_IN_BYTES_32 * my_image->channels)+(filesize*my_image->channels); i += my_image->channels)
	{
		const RGB pixel = { my_image->pixel_array[i], my_image->pixel_array[i + 1], my_image->pixel_array[i + 2] };
		Byte data_extracted = Decode(pixel);
		fwrite(&data_extracted, sizeof(Byte), 1, my_file->file_handler);
		VERBOSE_ON printf("Pixel %d (%d,%d,%d) : %d \n", (i - HEADER_SIZE_IN_BYTES_32/my_image->channels) / my_image->channels, my_image->pixel_array[i], my_image->pixel_array[i + 1], my_image->pixel_array[i + 2], data_extracted);
	}

	printf("File \"%s\" have been extracted to \"%s\"", (char*)&my_header.header[10], output->count > 0 ? output->filename[0] : buf);

	//Clean
	VERBOSE_ON printf("\n");
	ImageDestroy(&my_image);
	FileUnload(&my_file);
	return 0;
}
