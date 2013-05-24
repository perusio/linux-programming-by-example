/* ch12-mktemp.c --- demonstrate naive use of mktemp().
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

	strcpy(fname, template);
	mktemp(fname);

	/* RACE CONDITION WINDOW OPENS */

	printf("Filename is %s\n", fname);

	/* RACE CONDITION WINDOW LASTS TO HERE */

	fd = open(fname, O_CREAT|O_RDWR|O_TRUNC, 0600);
	write(fd, mesg, strlen(mesg));
	close(fd);

	/* unlink(fname); */

	return 0;
}
