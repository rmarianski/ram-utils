#ifndef RAM_ERR_H
#define RAM_ERR_H

#include <stdio.h>

#define perr_die_if(cond, msg) if (cond) { perror(msg); exit(EXIT_FAILURE); }
#define die_if(cond, ...) if (cond) { fprintf(stderr, ##__VA_ARGS__); exit(EXIT_FAILURE); }
#define die_usage(progname, msg) fprintf(stderr, "Usage: %s %s\n", progname,  msg); exit(EXIT_FAILURE);

#endif
