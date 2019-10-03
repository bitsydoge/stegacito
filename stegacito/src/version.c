#include "version.h"

unsigned char version_number = 1;
const char * version_name[] =
{
	"PREDEV",
	"0.0.1",
	"0.0.2"
};

unsigned char GetVersionNumber()
{
	return version_number;
}
const char * GetVersionName()
{
	return version_name[version_number];
}