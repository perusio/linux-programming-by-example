/* ch09-pipedemo.c --- demonstrate I/O with a pipe. */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

/* main --- create a pipe, write to it, and read from it. */

int main(int argc, char **argv)
{
	static const char mesg[] = "Don't Panic!";	/* a famous message */
	char buf[BUFSIZ];
	ssize_t rcount, wcount;
	int pipefd[2];
	size_t l;

	if (pipe(pipefd) < 0) {
		fprintf(stderr, "%s: pipe failed: %s\n", argv[0],
			strerror(errno));
		exit(1);
	}

	printf("Read end = fd %d, write end = fd %d\n",
		pipefd[0], pipefd[1]);

	l = strlen(mesg);
	if ((wcount = write(pipefd[1], mesg, l)) != l) {
		fprintf(stderr, "%s: write failed: %s\n", argv[0],
			strerror(errno));
		exit(1);
	}

	if ((rcount = read(pipefd[0], buf, BUFSIZ)) != wcount) {
		fprintf(stderr, "%s: read failed: %s\n", argv[0],
			strerror(errno));
		exit(1);
	}

	buf[rcount] = '\0';

	printf("Read <%s> from pipe\n", buf);
	(void) close(pipefd[0]);
	(void) close(pipefd[1]);

	return 0;
}
