#include "stg_verbose.h"

int verbose = 0;

void SetVerbose(int is_verbose)
{
	verbose = is_verbose;
}

int IsVerbose()
{
	return verbose;
}