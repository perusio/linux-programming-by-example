/* ch10-catchint.c --- catch a SIGINT, at least once. */

#include <signal.h>
#include <string.h>
#include <unistd.h>

/* handler --- simple signal handler. */

void handler(int signum)
{
	char buf[200], *cp;
	int offset;

	/* Jump through hoops to avoid fprintf(). */
	strcpy(buf, "handler: caught signal ");
	cp = buf + strlen(buf);	/* cp points at terminating '\0' */
	if (signum > 100)	/* unlikely */
		offset = 3;
	else if (signum > 10)
		offset = 2;
	else
		offset = 1;
	cp += offset;

	*cp-- = '\0';		/* terminate string */
	while (signum > 0) {	/* work backwards, filling in digits */
		*cp-- = (signum % 10) + '0';
		signum /= 10;
	}
	strcat(buf, "\n");
	(void) write(2, buf, strlen(buf));
}

/* main --- set up signal handling and go into infinite loop */

int main(void)
{
	(void) signal(SIGINT, handler);

	for (;;)
		pause();	/* wait for a signal, see later in the chapter */

	return 0;
}
