#ifndef FILE_H
#define FILE_H

#include "header.h"
#include <stdio.h>

struct File
{
	FILE* file_handler;
	HEADER_FILE_SIZE_CONTAINER_TYPE_64 size;

}; typedef struct File File;

HEADER_FILE_SIZE_CONTAINER_TYPE_64 GetSizeFileInBytes(FILE* file);
File* FileLoad(const char* path, char* mode);
void FileUnload(File** file_to_delete);

#endif // FILE_H