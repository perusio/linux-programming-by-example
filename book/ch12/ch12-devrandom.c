/* ch12-devrandom.c --- generate die rolls, using /dev/urandom. */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char *die_faces[] = {	/* ASCII graphics rule! */
	"       ",
	"   *   ",	/* 1 */
	"       ",

	"       ",
	" *   * ",	/* 2 */
	"       ",

	"       ",
	" * * * ",	/* 3 */
	"       ",

	" *   * ",
	"       ",	/* 4 */
	" *   * ",

	" *   * ",
	"   *   ",	/* 5 */
	" *   * ",

	" * * * ",
	"       ",	/* 6 */
	" * * * ",
};

/* myrandom --- return data from /dev/urandom as unsigned long */

unsigned long myrandom(void)
{
	static int fd = -1;
	unsigned long data;

	if (fd == -1)
		fd = open("/dev/urandom", O_RDONLY);

	if (fd == -1 || read(fd, & data, sizeof data) <= 0)
		return random();	/* fall back */

	return data;
}

/* main --- print N different die faces */

int main(int argc, char **argv)
{
	int nfaces;
	int i, j, k;

	if (argc != 2) {
		fprintf(stderr, "usage: %s number-die-faces\n", argv[0]);
		exit(1);
	}

	nfaces = atoi(argv[1]);

	if (nfaces <= 0) {
		fprintf(stderr, "usage: %s number-die-faces\n", argv[0]);
		fprintf(stderr, "\tUse a positive number!\n");
		exit(1);
	}

	for (i = 1; i <= nfaces; i++) {
		j = myrandom() % 6;		/* force to range 0 <= j <= 5 */
		printf("+-------+\n");
		for (k = 0; k < 3; k++)
			printf("|%s|\n", die_faces[(j * 3) + k]);
		printf("+-------+\n");
		putchar('\n');
	}

	return 0;
}
