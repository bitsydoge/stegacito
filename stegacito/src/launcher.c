#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"

#include "errorcode.h"
#include "decoder.h"
#include "encoder.h"
#include "verbose.h"
#include "external/argtable3.h"
#include "version.h"

// Argument	Type On, Off, Multiple On
struct arg_lit* verbose, * help, * version, * extract;
// File lists
struct arg_file* output, * file, * image;
struct arg_end* end;
char ProgExecName[] = "stegacito.exe";
char ProgTitle[] = "Stegacito";

int main(int argc, char* argv[])
{
	void* argtable[] =
	{
		file = arg_filen(NULL, NULL, "<file>", 0, 1, "input file"),
		image = arg_filen("i", "image", "<imageFile>", 1, 1, "image that contain/will contain file "),
		output = arg_filen("o", "output", "<output>", 0, 1, "output file name"),
		extract = arg_litn("e", "extract", 0, 1, "enable extract mode"),
		help = arg_litn("h", "help", 0, 1, "display this help"),
		version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
		verbose = arg_litn("v", "verbose", 0, 1, "verbose output and exit"),
		end = arg_end(20),
	};
	// Parse the ArgTable
	const int nerrors = arg_parse(argc, argv, argtable);
	if(version->count!=0 || help->count!=0)
	{
		// Show Help if needed
		if (help->count > 0)
		{
			printf("usage: %s", ProgExecName);
			arg_print_syntax(stdout, argtable, "\n\n");
			arg_print_glossary(stdout, argtable, "  %-25s %s\n");
			puts("");
		}

		if (version->count > 0)
		{
			printf("Version : %s\n", GetVersionName());
		}
	}
	else
	{
		// If the Error the Parser returned
		if (nerrors > 0)
		{
			// Display it
			arg_print_errors(stdout, end, ProgExecName);
			if (help->count == 0)
				printf("Try '%s --help' for more information.\n", ProgExecName);
		}
		else
		{
			SetVerbose(verbose->count > 0 ? 1 : 0);
			if (extract->count > 0 && file->count == 0)
			{
				decoder_main(image, output);
			}
			else if (extract->count == 0 && file->count > 0)
			{
				encoder_main(file, image, output);
			}
		}		
	}
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}