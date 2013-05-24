/* ch06-sortdir.c --- Demonstrate scandir(), alphasort(). */

#include <stdio.h>		/* for printf() etc. */
#include <errno.h>		/* for errno */
#include <sys/types.h>		/* for system types */
#include <dirent.h>		/* for directory functions */

char *myname;
int process(const char *dir);

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

/* nodots --- ignore dot files, for use by scandir() */

int
nodots(const struct dirent *dp)
{
	return (dp->d_name[0] != '.');
}

/*
 * process --- do something with the directory, in this case,
 *             print inode/name pairs on standard output.
 *             Return 0 if all OK, 1 otherwise.
 */

int
process(const char *dir)
{
	DIR *dp;
	struct dirent **entries;
	int nents, i;

	nents = scandir(dir, & entries, nodots, alphasort);
	if (nents < 0) {
		fprintf(stderr, "%s: scandir failed: %s\n", myname,
				strerror(errno));
		return 1;
	}

	for (i = 0; i < nents; i++) {
		printf("%8ld %s\n", entries[i]->d_ino, entries[i]->d_name);
		free(entries[i]);
	}

	free(entries);

	return 0;
}
