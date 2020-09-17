#include "error_handler.h"
#include <assert.h>
#include <string.h>

#define CR "\x1b[0m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define BON "\e[1m"
#define BOFF "\e[0m"

char * fname = NULL;

void error_handler_init(const char * name) {
	fname = strdup(name);
}

void error_handler_destroy() {
	if (!fname) return;
	free(fname);
}

void error(ErrorType et, size_t line, const char * format, ...) {
	assert(fname != NULL);
	va_list argptr;
	va_start(argptr, format);
	fprintf(stderr, BON "%s:%u:" BOFF, fname, line);
	switch(et) {
		case(ErrorType::Error):
			fprintf(stderr, BON RED " Error: " CR BOFF);
			break;
		case(ErrorType::Warning):
			fprintf(stderr, BON YELLOW " Warning: " CR BOFF);
			break;
		case(ErrorType::FatalError):
			fprintf(stderr, BON RED " Fatal Error: " CR BOFF);
			break;
		default:
			fprintf(stderr, BON CYAN " Unkown Error Type: " CR BOFF);
	}
	vfprintf(stderr, format, argptr);
	va_end(argptr);
}
