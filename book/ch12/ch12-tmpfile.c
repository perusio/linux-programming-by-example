/* ch12-tmpfile.c --- demonstrate tmpfile().
                      Error checking omitted for brevity */

#include <stdio.h>

int main(void)
{
	static char mesg[] =
		"Here's lookin' at you, kid!";	/* beats "hello, world" */
	FILE *fp;
	char buf[BUFSIZ];

	fp = tmpfile();				/* Get temp file */
	fprintf(fp, "%s", mesg);		/* Write to it */
	fflush(fp);				/* Force it out */

	rewind(fp);				/* Move to front */
	fgets(buf, sizeof buf, fp);		/* Read contents */

	printf("Got back <%s>\n", buf);		/* Print retrieved data */

	fclose(fp);				/* Close file, goes away */
	return 0;				/* All done */
}
