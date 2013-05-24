/* ch13-compare.c --- demonstrate strcmp() vs. strcoll() */

#include <stdio.h>
#include <locale.h>
#include <string.h>

int main(void)
{
#define STRBUFSIZE	1024
	char locale[STRBUFSIZE], curloc[STRBUFSIZE];
	char left[STRBUFSIZE], right[STRBUFSIZE];
	char buf[BUFSIZ];
	int count;

	setlocale(LC_ALL, "");				/* set to env locale */
	strcpy(curloc, setlocale(LC_ALL, NULL));	/* save it */

	printf("--> "); fflush(stdout);
	while (fgets(buf, sizeof buf, stdin) != NULL) {
		locale[0] = '\0';
		count = sscanf(buf, "%s %s %s", left, right, locale);
		if (count < 2)
			break;

		if (*locale) {
			setlocale(LC_ALL, locale);
			strcpy(curloc, locale);
		}

		printf("%s: strcmp(\"%s\", \"%s\") is %d\n", curloc, left,
				right, strcmp(left, right));
		printf("%s: strcoll(\"%s\", \"%s\") is %d\n", curloc, left,
				right, strcoll(left, right));

		printf("\n--> "); fflush(stdout);
	}

	exit(0);
}
