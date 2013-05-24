/* ch06-groupinfo.c --- Demonstrate getgrent() and struct group */

#include <stdio.h>
#include <sys/types.h>
#include <grp.h>

extern void print_group(const struct group *gr);

/* main --- print group lines for user named in argv[1] */

int
main(int argc, char **argv)
{
	struct group *gr;
	int i;

	if (argc != 2) {
		fprintf(stderr, "usage: %s user\n", argv[0]);
		exit(1);
	}

	while ((gr = getgrent()) != NULL)
		for (i = 0; gr->gr_mem[i] != NULL; i++)
			if (strcmp(gr->gr_mem[i], argv[1]) == 0)
				print_group(gr);

	endgrent();

	exit(0);
}

/* print_group --- print a group record */

void
print_group(const struct group *gr)
{
	int i;

	printf("%s:%s:%ld:", gr->gr_name, gr->gr_passwd, (long) gr->gr_gid);

	for (i = 0; gr->gr_mem[i] != NULL; i++) {
		printf("%s", gr->gr_mem[i]);
		if (gr->gr_mem[i+1] != NULL)
			putchar(',');
	}

	putchar('\n');
}
