/* ch15-badmem3.c --- do bad things with nondynamic memory */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int a_var;	/* Both of these are uninitialized */
	int b_var;

	/* Valgrind won't flag this; see text. */
	a_var = b_var;

	/* Use uninitialized memory; this is flagged. */
	printf("a_var = %d\n", a_var);

	return 0;
}
