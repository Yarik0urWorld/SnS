#include <stdio.h>
#include <string.h>

#include "all.h"

FILE *logfile = NULL;
int color_mode = LOGCOLOR_AUTO;
int loglevel = LOGLEVEL_DEBUG;

void logMessage_(const char* file, int line, int loglvl, const char* msg) {
	char loglvl_str[16];
	
	switch (loglvl) {
		case LOGLEVEL_FATAL:
			strcpy(&loglvl_str[0], "[FATAL]");
			break;
		case LOGLEVEL_ERROR:
			strcpy(&loglvl_str[0], "[ERROR]");
			break;
		case LOGLEVEL_WARN:
			strcpy(&loglvl_str[0], "[WARN] ");
			break;
		case LOGLEVEL_INFO:
			strcpy(&loglvl_str[0], "[INFO] ");
			break;
		case LOGLEVEL_DEBUG:
			strcpy(&loglvl_str[0], "[DEGUG]");
			break;
	}
	if (loglvl <= loglevel) {
		fprintf(logfile, "[%.4f] %s line %d at %s: %s\n", gettime() - t_global_begin, &loglvl_str[0], line, file, msg);
	}
}
