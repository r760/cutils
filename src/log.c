#include <time.h>

char *date_time()
{
    time_t now = time(0);
    char *date_time = ctime(&now);

    size_t i = 0;
    while (date_time[i] != '\0') {
        if (date_time[i] == '\n') {
            date_time[i] = '\0';
        }
        i++;
    }

    return date_time;
}
