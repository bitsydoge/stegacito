#include "version.h"

unsigned char version_number = 2;
const char * version_name[] =
{
	"PREDEV",
	"0.0.1",
	"1.0.0"
};

unsigned char GetVersionNumber()
{
	return version_number;
}
const char * GetVersionName()
{
	return version_name[version_number];
}