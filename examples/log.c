#include <limits.h>
#include <log.h>
#include <logic.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a >= b) ? a : b

int addi(int a, int b)
{
    LOG_INFO("adding '%d' and '%d'", a, b);
    int temp = a + b;
    LOG_DEBUG("'%d' + '%d' = '%d'", a, b, temp);
    LOG_ERROR(IMPLIES((a >= 0 && b >= 0), temp >= 0), error, "integer overflow");
    LOG_ERROR(IMPLIES((a < 0 && b < 0), temp < 0), error, "integer overflow");
    return temp;
error:
    return max(a, b);
}

int multi(int a, int b)
{
    LOG_INFO("multiplying '%d' and '%d'", a, b);
    int temp = a * b;
    LOG_DEBUG("'%d' * '%d' = '%d'", a, b, temp);
    LOG_ERROR(IMPLIES((a >= 0 && b >= 0), temp >= 0), error, "integer overflow");
    LOG_ERROR(IMPLIES((a < 0 && b < 0), temp < 0), error, "integer overflow");
    return temp;
error:
    return max(a, b);
}

int main(int argc, char *argv[])
{
    LOG_WARN_NO_JUMP(argc == 2, "ignoring command line arguments");
    int retval = 0;

    // catch integer overflow
    retval = addi(INT_MAX, INT_MAX);
    printf("retval '%d'\n", retval);

    // catch integer overflow
    retval = addi(INT_MAX * -1, INT_MAX * -1);
    printf("retval '%d'\n", retval);

    // catch integer overflow
    retval = multi(INT_MAX, INT_MAX);
    printf("retval '%d'\n", retval);

    // catch integer overflow
    retval = multi(INT_MAX * -1, INT_MAX * -1);
    printf("retval '%d'\n", retval);

    return 0;
}
