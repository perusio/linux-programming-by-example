/* ch05-trymkdir.c --- Demonstrate mkdir() behavior.
			Courtesy of Nelson H.F. Beebe. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS 0
#endif

void do_test(const char *path)
{
	int retcode;

	errno = 0;
	retcode = mkdir(path, 0755);
	printf("mkdir(\"%s\") returns %d: errno = %d [%s]\n",
		 path, retcode, errno, strerror(errno));
}

int main(void)
{
	do_test("/tmp/t1/t2/t3/t4");
	do_test("/tmp/t1/t2/t3");
	do_test("/tmp/t1/t2");
	do_test("/tmp/t1");

	do_test("/tmp/u1");
	do_test("/tmp/u1/u2");
	do_test("/tmp/u1/u2/u3");
	do_test("/tmp/u1/u2/u3/u4");

	do_test("/tmp/v1/");
	do_test("/tmp/v1/v2/");
	do_test("/tmp/v1/v2/v3/");
	do_test("/tmp/v1/v2/v3/v4/");

	return (EXIT_SUCCESS);
}
