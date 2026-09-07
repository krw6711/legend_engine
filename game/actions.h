#ifndef ACTION_H
#define ACTION_H
#include "../global/globals.h"
#include "../global/dynamic_array.h"

extern void (**functions)(void);

int init_functions(void);

#endif