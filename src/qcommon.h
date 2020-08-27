#ifndef QCOMMON_H
#define QCOMMON_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	LOG_DEBUG,
	LOG_ERROR,
	LOG_WARNING,
} logLevel_t;

void		Com_Printf(logLevel_t level, const char *format, ...);

#endif
