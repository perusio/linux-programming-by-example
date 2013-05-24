/* ch14-lockall.c --- Demonstrate mandatory locking. */

#include <stdio.h>		/* for fprintf(), stderr, BUFSIZ */
#include <errno.h>		/* declare errno */
#include <fcntl.h>		/* for flags for open() */
#include <string.h>		/* declare strerror() */
#include <unistd.h>		/* for ssize_t */
#include <sys/types.h>
#include <sys/stat.h>		/* for mode_t */

int
main(int argc, char **argv)
{
	int fd;
	int i, j;
	mode_t rw_mode;
	static char message[] = "hello, world\n";
	struct flock lock;

	if (argc != 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(1);
	}
	
	rw_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;                /* 0644 */
	fd = open(argv[1], O_RDWR|O_TRUNC|O_CREAT|O_EXCL, rw_mode);
	if (fd < 0) {
		fprintf(stderr, "%s: %s: cannot open for read/write: %s\n",
				argv[0], argv[1], strerror(errno));
		(void) close(fd);
		return 1;
	}

	if (write(fd, message, strlen(message)) != strlen(message)) {
		fprintf(stderr, "%s: %s: cannot write: %s\n",
				argv[0], argv[1], strerror(errno));
		(void) close(fd);
		return 1;
	}

	rw_mode |= S_ISGID;	/* add mandatory lock bit */

	if (fchmod(fd, rw_mode) < 0) {
		fprintf(stderr, "%s: %s: cannot change mode to %o: %s\n",
				argv[0], argv[1], rw_mode, strerror(errno));
		(void) close(fd);
		return 1;
	}

	/* lock the file */
	memset(& lock, '\0', sizeof(lock));
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;			/* whole-file lock */
	lock.l_type = F_WRLCK;		/* write lock */

	if (fcntl(fd, F_SETLK, & lock) < 0) {
		fprintf(stderr, "%s: %s: cannot lock the file: %s\n",
				argv[0], argv[1], strerror(errno));
		(void) close(fd);
		return 1;
	}

	pause();

	(void) close(fd);

	return 0;
}
