/* ch08-chdir.c --- demonstrate chdir() and fchdir().
                    Error checking omitted for brevity */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	struct stat sbuf;

	fd = open(".", O_RDONLY);	/* open directory for reading */
	fstat(fd, & sbuf);		/* obtain info, need original permissions */
	chdir("..");			/* `cd ..' */
	fchmod(fd, 0);			/* zap permissions on original directory */

	if (fchdir(fd) < 0)		/* try to `cd' back, should fail */
		perror("fchdir back");

	fchmod(fd, sbuf.st_mode & 07777);	/* restore original permissions */
	close(fd);			/* all done */

	return 0;
}
