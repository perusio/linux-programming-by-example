/* ch12-random.c --- generate die rolls, using random(). */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
	char state[256];
	time_t now;

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

	(void) time(& now);	/* seed with time of day and PID */
	(void) initstate((unsigned int) (now + getpid()), state, sizeof state);
	(void) setstate(state);

	for (i = 1; i <= nfaces; i++) {
		j = random() % 6;		/* force to range 0 <= j <= 5 */
		printf("+-------+\n");
		for (k = 0; k < 3; k++)
			printf("|%s|\n", die_faces[(j * 3) + k]);
		printf("+-------+\n\n");
	}

	return 0;
}
