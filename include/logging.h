#pragma once
#ifndef LOGGING_H
#define LOGGING_H

typedef enum
{
    ERROR = 1,
    WARN  = 2,
    INFO  = 3,
    TRACE = 4,
    DEBUG = 5
} log_level;

int set_log_level(int level);
void logging(int level, const char * format, ...);

#endif 