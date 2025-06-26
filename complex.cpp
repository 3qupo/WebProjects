#include "complex.h"

long int post_inc(long int* arg)
{
    long int old_arg = *arg;
    *arg = *arg + 1;

    return old_arg;
}

long int pref_inc(long int* arg)
{
    *arg = *arg + 1;
    return *arg;
}