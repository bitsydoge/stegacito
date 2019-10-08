#ifndef VERBOSE_H
#define VERBOSE_H

void SetVerbose(int is_verbose);
int IsVerbose();

#define VERBOSE_ON if(IsVerbose()>0)

#endif // VERBOSE_H