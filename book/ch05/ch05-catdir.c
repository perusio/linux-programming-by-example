/* ch05-catdir.c --- Demonstrate opendir(), readdir(), closedir(). */

#include <stdio.h>		/* for printf() etc. */
#include <errno.h>		/* for errno */
#include <sys/types.h>		/* for system types */
#include <dirent.h>		/* for directory functions */

char *myname;
int process(char *dir);

/* main --- loop over directory arguments */

int main(int argc, char **argv)
{
	int i;
	int errs = 0;

	myname = argv[0];

	if (argc == 1)
		errs = process(".");	/* default to current directory */
	else
		for (i = 1; i < argc; i++)
			errs += process(argv[i]);

	return (errs != 0);
}

/*
 * process --- do something with the directory, in this case,
 *             print inode/name pairs on standard output.
 *             Returns 0 if all ok, 1 otherwise.
 */

int
process(char *dir)
{
	DIR *dp;
	struct dirent *ent;

	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "%s: %s: cannot open for reading: %s\n",
				myname, dir, strerror(errno));
		return 1;
	}

	errno = 0;
	while ((ent = readdir(dp)) != NULL)
		printf("%8ld %s\n", ent->d_ino, ent->d_name);

	if (errno != 0) {
		fprintf(stderr, "%s: %s: reading directory entries: %s\n",
				myname, dir, strerror(errno));
		return 1;
	}

	if (closedir(dp) != 0) {
		fprintf(stderr, "%s: %s: closedir: %s\n",
				myname, dir, strerror(errno));
		return 1;
	}

	return 0;
}
