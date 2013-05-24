/* ch12-grep.c --- Simple version of grep using POSIX R.E. functions. */

#define _GNU_SOURCE 1		/* for getline() */
#include <stdio.h>
#include <errno.h>
#include <regex.h>
#include <unistd.h>
#include <sys/types.h>

char *myname;			/* for error messages */
int ignore_case = 0;		/* -i option: ignore case */
int extended = 0;		/* -E option: use extended RE's */
int errors = 0;			/* number of errors */

regex_t pattern;		/* pattern to match */

void compile_pattern(const char *pat);
void process(const char *name, FILE *fp);
void usage(void);

/* main --- process options, open files */

int main(int argc, char **argv)
{
	int c;
	int i;
	FILE *fp;

	myname = argv[0];
	while ((c = getopt(argc, argv, ":iE")) != -1) {
		switch (c) {
		case 'i':
			ignore_case = 1;
			break;
		case 'E':
			extended = 1;
			break;
		case '?':
			usage();
			break;
		}
	}

	if (optind == argc)		/* sanity check */
		usage();

	compile_pattern(argv[optind]);	/* compile the pattern */
	if (errors)			/* compile failed */
		return 1;
	else
		optind++;

	if (optind == argc)		/* no files, default to stdin */
		process("standard input", stdin);
	else {
		/* loop over files */
		for (i = optind; i < argc; i++) {
			if (strcmp(argv[i], "-") == 0)
				process("standard input", stdin);
			else if ((fp = fopen(argv[i], "r")) != NULL) {
				process(argv[i], fp);
				fclose(fp);
			} else {
				fprintf(stderr, "%s: %s: could not open: %s\n",
					argv[0], argv[i], strerror(errno));
				errors++;
			}
		}
	}

	regfree(& pattern);
	return errors != 0;
}

/* compile_pattern --- compile the pattern */

void compile_pattern(const char *pat)
{
	int flags = REG_NOSUB;	/* don't need where-matched info */
	int ret;
#define MSGBUFSIZE	512	/* arbitrary */
	char error[MSGBUFSIZE];

	if (ignore_case)
		flags |= REG_ICASE;
	if (extended)
		flags |= REG_EXTENDED;

	ret = regcomp(& pattern, pat, flags);
	if (ret != 0) {
		(void) regerror(ret, & pattern, error, sizeof error);
		fprintf(stderr, "%s: pattern `%s': %s\n", myname, pat, error);
		errors++;
	}
}

/* process --- read lines of text and match against the pattern */

void process(const char *name, FILE *fp)
{
	char *buf = NULL;
	size_t size = 0;
	char error[MSGBUFSIZE];
	int ret;

	while (getline(& buf, &size, fp) != -1) {
		ret = regexec(& pattern, buf, 0, NULL, 0);
		if (ret != 0) {
			if (ret != REG_NOMATCH) {
				(void) regerror(ret, & pattern, error, sizeof error);
				fprintf(stderr, "%s: file %s: %s\n", myname, name, error);
				free(buf);
				errors++;
				return;
			}
		} else
			printf("%s: %s", name, buf);	/* print matching lines */
	}
	free(buf);
}

/* usage --- print usage message and exit */

void usage(void)
{
	fprintf(stderr, "usage: %s [-i] [-E] pattern [ files ... ]\n", myname);
	exit(1);
}
