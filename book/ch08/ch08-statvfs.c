/* ch08-statvfs.c --- demonstrate statvfs */

/* NOTE: GNU/Linux specific! */

#include <stdio.h>
#include <errno.h>
#include <mntent.h>	/* for getmntent(), et al. */
#include <unistd.h>	/* for getopt() */
#include <sys/types.h>
#include <sys/statvfs.h>

void process(const char *filename);
void do_statvfs(const struct mntent *fs);

int errors = 0;
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
	return (errors != 0);
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
		do_statvfs(fs);

	endmntent(fp);
}

/* do_statvfs --- Use statvfs and print info */

void do_statvfs(const struct mntent *fs)
{
	struct statvfs vfs;

	if (fs->mnt_fsname[0] != '/')	/* skip nonreal filesystems */
		return;

	if (statvfs(fs->mnt_dir, & vfs) != 0) {
		fprintf(stderr, "%s: %s: statvfs failed: %s\n",
			myname, fs->mnt_dir, strerror(errno));
		errors++;
		return;
	}

	printf("%s, mounted on %s:\n", fs->mnt_dir, fs->mnt_fsname);
	printf("\tf_bsize: %ld\n",  (long) vfs.f_bsize);
	printf("\tf_frsize: %ld\n", (long) vfs.f_frsize);
	printf("\tf_blocks: %lu\n", (unsigned long) vfs.f_blocks);
	printf("\tf_bfree: %lu\n",  (unsigned long) vfs.f_bfree);
	printf("\tf_bavail: %lu\n", (unsigned long) vfs.f_bavail);
	printf("\tf_files: %lu\n",  (unsigned long) vfs.f_files);
	printf("\tf_ffree: %lu\n",  (unsigned long) vfs.f_ffree);
	printf("\tf_favail: %lu\n", (unsigned long) vfs.f_favail);
	printf("\tf_fsid: %#lx\n",  (unsigned long) vfs.f_fsid);

	printf("\tf_flag: ");
	if (vfs.f_flag == 0)
		printf("(none)\n");
	else {
		if ((vfs.f_flag & ST_RDONLY) != 0)
			printf("ST_RDONLY ");
		if ((vfs.f_flag & ST_NOSUID) != 0)
			printf("ST_NOSUID");
		printf("\n");
	}

	printf("\tf_namemax: %#ld\n", (long)vfs.f_namemax);
}
