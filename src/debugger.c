#include "../include/debugger.h"

void    debug(char *msg)
{
    printf("DEBUG: %s\n", msg);
}

void    fatal_debug(char *msg)
{
    printf("FATAL DEBUG: %s\n", msg);
    exit(1);
}
