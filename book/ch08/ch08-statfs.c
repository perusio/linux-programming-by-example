/* ch08-statfs.c --- demonstrate Linux statfs */

/* NOTE: GNU/Linux specific! */

#include <stdio.h>
#include <errno.h>
#include <mntent.h>	/* for getmntent(), et al. */
#include <unistd.h>	/* for getopt() */
#include <sys/types.h>
#include <sys/vfs.h>

/* Defines taken from statfs(2) man page: */
#define AFFS_SUPER_MAGIC      0xADFF
#define EFS_SUPER_MAGIC       0x00414A53
#define EXT_SUPER_MAGIC       0x137D
#define EXT2_OLD_SUPER_MAGIC  0xEF51
#define EXT2_SUPER_MAGIC      0xEF53
#define HPFS_SUPER_MAGIC      0xF995E849
#define ISOFS_SUPER_MAGIC     0x9660
#define MINIX_SUPER_MAGIC     0x137F /* orig. minix */
#define MINIX_SUPER_MAGIC2    0x138F /* 30-char minix */
#define MINIX2_SUPER_MAGIC    0x2468 /* minix V2 */
#define MINIX2_SUPER_MAGIC2   0x2478 /* minix V2, 30 char names */
#define MSDOS_SUPER_MAGIC     0x4d44
#define NCP_SUPER_MAGIC       0x564c
#define NFS_SUPER_MAGIC       0x6969
#define PROC_SUPER_MAGIC      0x9fa0
#define SMB_SUPER_MAGIC       0x517B
#define XENIX_SUPER_MAGIC     0x012FF7B4
#define SYSV4_SUPER_MAGIC     0x012FF7B5
#define SYSV2_SUPER_MAGIC     0x012FF7B6
#define COH_SUPER_MAGIC       0x012FF7B7
#define UFS_MAGIC             0x00011954
#define XFS_SUPER_MAGIC       0x58465342
#define _XIAFS_SUPER_MAGIC    0x012FD16D

void process(const char *filename);
void do_statfs(const struct mntent *fs);

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
		do_statfs(fs);

	endmntent(fp);
}

/* type2str --- convert fs type to printable string, from statfs(2) */

const char *type2str(long type)
{
	static struct fsname {
		long type;
		const char *name;
	} table[] = {
		{ AFFS_SUPER_MAGIC, "AFFS" },
		{ COH_SUPER_MAGIC, "COH" },
		{ EXT2_OLD_SUPER_MAGIC, "OLD EXT2" },
		{ EXT2_SUPER_MAGIC, "EXT2" },
		{ HPFS_SUPER_MAGIC, "HPFS" },
		{ ISOFS_SUPER_MAGIC, "ISOFS" },
		{ MINIX2_SUPER_MAGIC, "MINIX V2" },
		{ MINIX2_SUPER_MAGIC2, "MINIX V2 30 char" },
		{ MINIX_SUPER_MAGIC, "MINIX" },
		{ MINIX_SUPER_MAGIC2, "MINIX 30 char" },
		{ MSDOS_SUPER_MAGIC, "MSDOS" },
		{ NCP_SUPER_MAGIC, "NCP" },
		{ NFS_SUPER_MAGIC, "NFS" },
		{ PROC_SUPER_MAGIC, "PROC" },
		{ SMB_SUPER_MAGIC, "SMB" },
		{ SYSV2_SUPER_MAGIC, "SYSV2" },
		{ SYSV4_SUPER_MAGIC, "SYSV4" },
		{ UFS_MAGIC, "UFS" },
		{ XENIX_SUPER_MAGIC, "XENIX" },
		{ _XIAFS_SUPER_MAGIC, "XIAFS" },
		{ 0, NULL },
	};
	static char unknown[100];
	int i;

	for (i = 0; table[i].type != 0; i++)
		if (table[i].type == type)
			return table[i].name;

	sprintf(unknown, "unknown type: %#x", type);
	return unknown;
}

/* do_statfs --- Use statfs and print info */

void do_statfs(const struct mntent *fs)
{
	struct statfs vfs;

	if (fs->mnt_fsname[0] != '/')	/* skip nonreal filesystems */
		return;

	if (statfs(fs->mnt_dir, & vfs) != 0) {
		fprintf(stderr, "%s: %s: statfs failed: %s\n",
			myname, fs->mnt_dir, strerror(errno));
		errors++;
		return;
	}

	printf("%s, mounted on %s:\n", fs->mnt_dir, fs->mnt_fsname);

	printf("\tf_type: %s\n", type2str(vfs.f_type));
	printf("\tf_bsize: %ld\n", vfs.f_bsize);
	printf("\tf_blocks: %ld\n", vfs.f_blocks);
	printf("\tf_bfree: %ld\n", vfs.f_bfree);
	printf("\tf_bavail: %ld\n", vfs.f_bavail);
	printf("\tf_files: %ld\n", vfs.f_files);
	printf("\tf_ffree: %ld\n", vfs.f_ffree);
	printf("\tf_namelen: %ld\n", vfs.f_namelen);
}
