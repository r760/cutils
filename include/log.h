#ifndef LOG_H
#define LOG_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

/**
 * get current data time (no newline)
 */
char *date_time();
enum LOG_TYPE { INFO, DEBUG, WARN, ERROR };

#ifdef N_LOG_COLORS
#define LOG_COLOR_BLUE   ""
#define LOG_COLOR_CYAN   ""
#define LOG_COLOR_GREEN  ""
#define LOG_COLOR_RED    ""
#define LOG_COLOR_RESET  ""
#define LOG_COLOR_YELLOW ""
#else
#define LOG_COLOR_BLUE   "\x1B[34m"
#define LOG_COLOR_CYAN   "\x1B[36m"
#define LOG_COLOR_GREEN  "\x1B[32m"
#define LOG_COLOR_RED    "\x1B[31m"
#define LOG_COLOR_RESET  "\x1B[0m"
#define LOG_COLOR_YELLOW "\x1B[33m"
#endif

#define LOG_TEMPLATE(LOG_TYPE, LOG_MESSAGE, ...) \
    if (LOG_TYPE == INFO) { \
        fprintf(stderr, "%s %s%s%s (%s:%d) %s() ", \
                date_time(), LOG_COLOR_GREEN, "INFO ", LOG_COLOR_RESET, __FILE__, __LINE__, __FUNCTION__); \
    } else if (LOG_TYPE == DEBUG) { \
        fprintf(stderr, "%s %s%s%s (%s:%d) %s() ", \
                date_time(), LOG_COLOR_CYAN, "DEBUG", LOG_COLOR_RESET, __FILE__, __LINE__, __FUNCTION__); \
    } else if (LOG_TYPE == WARN) { \
        fprintf(stderr, "%s %s%s%s (%s:%d) %s() ", \
                date_time(), LOG_COLOR_YELLOW, "WARN ", LOG_COLOR_RESET, __FILE__, __LINE__, __FUNCTION__); \
    } else { \
        fprintf(stderr, "%s %s%s%s (%s:%d) %s() ", \
                date_time(), LOG_COLOR_RED, "ERROR", LOG_COLOR_RESET, __FILE__, __LINE__, __FUNCTION__); \
    } \
    if (errno == 0) { \
        fprintf(stderr, " --> " LOG_MESSAGE "\n", ##__VA_ARGS__); \
    } else { \
        fprintf(stderr, " --> [strerror:%s%s%s] " LOG_MESSAGE "\n", LOG_COLOR_RED, \
                strerror(errno), LOG_COLOR_RESET, ##__VA_ARGS__); \
    } \
    errno = 0

#ifdef N_LOG_INFO
#define LOG_INFO(LOG_MESSAGE, ...)
#else
/**
 * print INFO message to log
 */
#define LOG_INFO(LOG_MESSAGE, ...) LOG_TEMPLATE(INFO, LOG_MESSAGE, ##__VA_ARGS__);
#endif

#ifdef N_LOG_DEBUG
#define LOG_DEBUG(LOG_MESSAGE, ...)
#else
/**
 * print DEBUG message to log
 */
#define LOG_DEBUG(LOG_MESSAGE, ...) LOG_TEMPLATE(DEBUG, LOG_MESSAGE, ##__VA_ARGS__);
#endif

#ifdef N_LOG_WARN
#define LOG_WARN(CHECK_CONDITION, GOTO_LABEL, LOG_MESSAGE, ...)
#define LOG_WARN_NO_JUMP(CHECK_CONDITION, LOG_MESSAGE, ...)
#else
/**
 * if check condition fails then print WARNING message to log and jump to user defined goto label,
 * otherwise do nothing
 */
#define LOG_WARN(CHECK_CONDITION, GOTO_LABEL, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(WARN, LOG_MESSAGE, ##__VA_ARGS__); \
        goto GOTO_LABEL; \
    }
/**
 * if check condition fails then print WARNING message to log,
 * otherwise do nothing
 */
#define LOG_WARN_NO_JUMP(CHECK_CONDITION, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(WARN, LOG_MESSAGE, ##__VA_ARGS__); \
    }
#endif 

#ifdef N_LOG_ERROR
#define LOG_ERROR(CHECK_CONDITION, GOTO_LABEL, LOG_MESSAGE, ...)
#define LOG_ERROR_NO_JUMP(CHECK_CONDITION, LOG_MESSAGE, ...)
#else
/**
 * if check condition fails then print ERROR message to log and jump to user defined goto label,
 * otherwise do nothing
 */
#define LOG_ERROR(CHECK_CONDITION, GOTO_LABEL, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(ERROR, LOG_MESSAGE, ##__VA_ARGS__); \
        goto GOTO_LABEL; \
    }
/**
 * if check condition fails then print ERROR message to log,
 * otherwise do nothing
 */
#define LOG_ERROR_NO_JUMP(CHECK_CONDITION, LOG_MESSAGE, ...) \
    if (!(CHECK_CONDITION)) { \
        LOG_TEMPLATE(ERROR, LOG_MESSAGE, ##__VA_ARGS__); \
    }
#endif

#endif
