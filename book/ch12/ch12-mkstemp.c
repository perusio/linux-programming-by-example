/* ch12-mkstemp.c --- demonstrate mkstemp().
                      Error checking omitted for brevity */

#include <stdio.h>
#include <fcntl.h>	/* for open flags */
#include <limits.h>	/* for PATH_MAX */

int main(void)
{
	static char template[] = "/tmp/myfileXXXXXX";
	char fname[PATH_MAX];
	static char mesg[] =
		"Here's lookin' at you, kid!\n";	/* beats "hello, world" */
	int fd;
	char buf[BUFSIZ];
	int n;

	strcpy(fname, template);		/* Copy template */
	fd = mkstemp(fname);			/* Create and open temp file */
	printf("Filename is %s\n", fname);	/* Print it for information */

	write(fd, mesg, strlen(mesg));		/* Write something to file */

	lseek(fd, 0L, SEEK_SET);		/* Rewind to front */
	n = read(fd, buf, sizeof(buf));		/* Read data back; NOT '\0' terminated! */
	printf("Got back: %.*s", n, buf);	/* Print it out for verification */

	close(fd);				/* Close file */
	unlink(fname);				/* Remove it */

	return 0;
}
