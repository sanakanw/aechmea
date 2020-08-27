#include "qcommon.h"

#include <stdarg.h>

const char* log_levels[3] = {
	"[DEBUG] ",
	"[ERROR] ",
	"[WARNING] ",
};

void Com_Printf(logLevel_t level, const char* format, ...) {
	va_list args;
	va_start(args, format);
	
	printf(log_levels[level]);
	
	vprintf(format, args);
	
	va_end(args);

	printf("\n");	
	
	if (level == LOG_ERROR)
		exit(-1);
}
