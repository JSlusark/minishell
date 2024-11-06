#ifndef GUARDS_H
#define GUARDS_H

#include <stdio.h>
#include <stdlib.h>

#define OOM_GUARDS(ptr, file, line) \
	((ptr) ? (ptr) : oom_guard_handler(file, line))

static inline void *oom_guard_handler(const char *file, int line)
{
	fprintf(stderr, "Out of memory error at %s:%d\n", file, line);
	exit(EXIT_FAILURE);
	return NULL; // This line will never be reached, but it prevents compiler warnings.
}

#endif // GUARDS_H
