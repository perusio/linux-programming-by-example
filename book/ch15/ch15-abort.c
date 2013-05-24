/* ch15-abort.c --- produce a core dump */

#include <stdio.h>
#include <stdlib.h>

/* recurse --- build up some function calls */

void recurse(void)
{
	static int i;

	if (++i == 3)
		abort();
	else
		recurse();
}

int main(int argc, char **argv)
{
	recurse();
}
