#ifndef LOG_H
#define LOG_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef E_LOG_COLORS
#define LOG_COLOR_BLUE   "\x1B[34m"
#define LOG_COLOR_CYAN   "\x1B[36m"
#define LOG_COLOR_GREEN  "\x1B[32m"
#define LOG_COLOR_RED    "\x1B[31m"
#define LOG_COLOR_RESET  "\x1B[0m"
#define LOG_COLOR_YELLOW "\x1B[33m"
#else
#define LOG_COLOR_BLUE   ""
#define LOG_COLOR_CYAN   ""
#define LOG_COLOR_GREEN  ""
#define LOG_COLOR_RED    ""
#define LOG_COLOR_RESET  ""
#define LOG_COLOR_YELLOW ""
#endif

#define LOG_TEMPLATE(LOG_TYPE, LOG_MESSAGE, ...) \
    if (LOG_TYPE == 0) { \
        fprintf(stderr, "%s %s%s%s (%s:%d) ", \
                __TIME__, LOG_COLOR_GREEN, "INFO ", LOG_COLOR_RESET, __FILE__, __LINE__); \
    } else if (LOG_TYPE == 1) { \
        fprintf(stderr, "%s %s%s%s (%s:%d)", \
                __TIME__, LOG_COLOR_CYAN, "DEBUG", LOG_COLOR_RESET, __FILE__, __LINE__); \
    } else if (LOG_TYPE == 2) { \
        fprintf(stderr, "%s %s%s%s (%s:%d)", \
                __TIME__, LOG_COLOR_YELLOW, "WARN ", LOG_COLOR_RESET, __FILE__, __LINE__); \
    } else { \
        fprintf(stderr, "%s %s%s%s (%s:%d)", \
                __TIME__, LOG_COLOR_RED, "ERROR", LOG_COLOR_RESET, __FILE__, __LINE__); \
    } \
    if (errno == 0) { \
        fprintf(stderr, "\t--> " LOG_MESSAGE "\n", ##__VA_ARGS__); \
    } else { \
        fprintf(stderr, "\t--> [strerror:%s%s%s] " LOG_MESSAGE "\n", LOG_COLOR_RED, \
                strerror(errno), LOG_COLOR_RESET, ##__VA_ARGS__); \
    } \
    errno = 0

#ifdef E_LOG_INFO
#define LOG_INFO(LOG_MESSAGE, ...) LOG_TEMPLATE(0, LOG_MESSAGE, ##__VA_ARGS__);
#else
#define LOG_INFO(LOG_MESSAGE, ...)
#endif

#ifdef E_LOG_DEBUG
#define LOG_DEBUG(LOG_MESSAGE, ...) LOG_TEMPLATE(1, LOG_MESSAGE, ##__VA_ARGS__);
#else
#define LOG_DEBUG(LOG_MESSAGE, ...)
#endif

#ifdef E_LOG_WARN
#define LOG_WARN(CHECK_CONDITION, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(2, LOG_MESSAGE, ##__VA_ARGS__); \
    }
#else
#define LOG_WARN(CHECK_CONDITION, LOG_MESSAGE, ...)
#endif 

#ifdef E_LOG_ERROR
#define LOG_ERROR(CHECK_CONDITION, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(3, LOG_MESSAGE, ##__VA_ARGS__); \
        goto error; \
    }
#else
#define LOG_ERROR(CHECK_CONDITION, LOG_MESSAGE, ...)
#endif

#endif
