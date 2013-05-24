/* ch08-mounted.c --- print a list of mounted filesystems */

/* NOTE: GNU/Linux specific! */

#include <stdio.h>
#include <errno.h>
#include <mntent.h>	/* for getmntent(), et al. */
#include <unistd.h>	/* for getopt() */

void process(const char *filename);
void print_mount(const struct mntent *fs);

char *myname;

/* main --- process options */

int main(int argc, char **argv)
{
	int c;
	char *file = "/etc/mtab";	/* default file to read */

	myname = argv[0];
	while ((c = getopt(argc, argv, "f:")) != -1) {
		switch (c) {
		case 'f':
			file = optarg;
			break;
		default:
			fprintf(stderr, "usage: %s [-f fstab-file]\n", argv[0]);
			exit(1);
		}
	}

	process(file);
	return 0;
}

/* process --- read struct mntent structures from file */

void process(const char *filename)
{
	FILE *fp;
	struct mntent *fs;

	fp = setmntent(filename, "r");	/* read only */
	if (fp == NULL) {
		fprintf(stderr, "%s: %s: could not open: %s\n",
			myname, filename, strerror(errno));
		exit(1);
	}

	while ((fs = getmntent(fp)) != NULL)
		print_mount(fs);

	endmntent(fp);
}

/* print_mount --- print a single mount entry */

void print_mount(const struct mntent *fs)
{
	printf("%s %s %s %s %d %d\n",
		fs->mnt_fsname,
		fs->mnt_dir,
		fs->mnt_type,
		fs->mnt_opts,
		fs->mnt_freq,
		fs->mnt_passno);
}
