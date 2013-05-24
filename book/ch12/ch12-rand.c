/* ch12-rand.c --- generate die rolls, using rand(). */

#include <stdio.h>
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
		j = rand() % 6;		/* force to range 0 <= j <= 5 */
		printf("+-------+\n");
		for (k = 0; k < 3; k++)
			printf("|%s|\n", die_faces[(j * 3) + k]);
		printf("+-------+\n\n");
	}

	return 0;
}
