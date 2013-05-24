/* ch08-getcwd.c --- demonstrate getcwd().
                     Error checking omitted for brevity */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	char buf[BUFSIZ];
	char *cp;

	cp = getcwd(buf, sizeof(buf));
	printf("Current dir: %s\n", buf);

	printf("Changing to ..\n");
	chdir("..");			/* `cd ..' */

	cp = getcwd(buf, sizeof(buf));
	printf("Current dir is now: %s\n", buf);

	return 0;
}
