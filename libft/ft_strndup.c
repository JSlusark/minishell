#include "libft.h"


/* #include <stdlib.h>
#include <string.h> */

char *ft_strndup(const char *s, size_t n)
{
	char *copy;

	//size_t len = ft_strnlen(s, n); // Find the minimum of n and strlen(s)
	copy = OOM_GUARDS(malloc(sizeof(char) * (n + 1)), __FILE__, __LINE__); 	// Allocate memory for the copy
	ft_memcpy(copy, s, n); // Copy up to `len` characters
	copy[n] = '\0';     // Null-terminate the string

	return (copy);
}
