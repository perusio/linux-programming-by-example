/* ch05-devnum.c --- Demonstrate stat(), major(), minor(). */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

int main(int argc, char **argv)
{
	struct stat sbuf;
	char *devtype;

	if (argc != 2) {
		fprintf(stderr, "usage: %s path\n", argv[0]);
		exit(1);
	}

	if (stat(argv[1], & sbuf) < 0) {
		fprintf(stderr, "%s: stat: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	if (S_ISCHR(sbuf.st_mode))
		devtype = "char";
	else if (S_ISBLK(sbuf.st_mode))
		devtype = "block";
	else {
		fprintf(stderr, "%s is not a block or character device\n", argv[1]);
		exit(1);
	}

	printf("%s: major: %d, minor: %d\n", devtype,
			major(sbuf.st_rdev), minor(sbuf.st_rdev));

	exit(0);
}
