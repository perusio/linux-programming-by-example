/* ch15-badmem2.c --- do bad things with memory, use dmalloc.h */

#include <stdio.h>
#include <stdlib.h>

#include "dmalloc.h"

int main(int argc, char **argv)
{
	char *p;
	int i;

	p = malloc(30);

	strcpy(p, "not 30 bytes");
	printf("p = <%s>\n", p);

	if (argc == 2) {
		if (strcmp(argv[1], "-b") == 0)
			p[42] = 'a';	/* touch outside the bounds */
		else if (strcmp(argv[1], "-f") == 0) {
			free(p);	/* free memory and then use it */
			p[0] = 'b';
		}
	}

	/* free(p); */

	return 0;
}
