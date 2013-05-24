/* ch09-run.c --- run a program with a different name and any arguments */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

/* main --- adjust argv and run named program */

int main(int argc, char **argv)
{
	char *path;

	if (argc < 3) {
		fprintf(stderr, "usage: %s path arg0 [ arg ... ]\n", argv[0]);
		exit(1);
	}

	path = argv[1];

	execv(path, argv + 2);	/* skip argv[0] and argv[1] */

	fprintf(stderr, "%s: execv() failed: %s\n", argv[0],
		strerror(errno));
	exit(1);
}
