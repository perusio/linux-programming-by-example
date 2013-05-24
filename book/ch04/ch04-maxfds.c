/* ch04-maxfds.c --- Demonstrate getdtablesize(). */

#include <stdio.h>		/* for fprintf(), stderr, BUFSIZ */
#include <unistd.h>		/* for ssize_t */

int
main(int argc, char **argv)
{
	printf("max fds: %d\n", getdtablesize());
	exit(0);
}
