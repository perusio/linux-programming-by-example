/* ch04-holes.c --- Demonstrate lseek() and holes in files. */

#include <stdio.h>		/* for fprintf(), stderr, BUFSIZ */
#include <errno.h>		/* declare errno */
#include <fcntl.h>		/* for flags for open() */
#include <string.h>		/* declare strerror() */
#include <unistd.h>		/* for ssize_t */
#include <sys/types.h>		/* for off_t, etc. */
#include <sys/stat.h>		/* for mode_t */

struct person {
	char name[10];		/* first name */
	char id[10];		/* ID number */
	off_t pos;		/* position in file, for demonstration */
} people[] = {
	{ "arnold", "123456789", 0 },
	{ "miriam", "987654321", 10240 },
	{ "joe",    "192837465", 81920 },
};

int
main(int argc, char **argv)
{
	int fd;
	int i, j;

	if (argc < 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666);
	if (fd < 0) {
		fprintf(stderr, "%s: %s: cannot open for read/write: %s\n",
				argv[0], argv[1], strerror(errno));
		return 1;
	}

	j = sizeof(people) / sizeof(people[0]);		/* count of elements */

	for (i = 0; i < j; i++) {
		if (lseek(fd, people[i].pos, SEEK_SET) < 0) {
			fprintf(stderr, "%s: %s: seek error: %s\n",
				argv[0], argv[1], strerror(errno));
			(void) close(fd);
			return 1;
		}

		if (write(fd, &people[i], sizeof(people[i])) != sizeof(people[i])) {
			fprintf(stderr, "%s: %s: write error: %s\n",
				argv[0], argv[1], strerror(errno));
			(void) close(fd);
			return 1;
		}
	}

	/* all ok here */
	(void) close(fd);
	return 0;
}
