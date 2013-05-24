/* ch02-printenv.c --- Print out the environment. */

#include <stdio.h>

extern char **environ;

int main(int argc, char **argv)
{
	int i;

	if (environ != NULL)
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);

	return 0;
}
