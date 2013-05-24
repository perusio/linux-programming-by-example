/* ch10-reap2.c --- demonstrate SIGCHLD management, one signal per child */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_KIDS	42
#define NOT_USED	-1

pid_t kids[MAX_KIDS];
size_t nkids = 0;
size_t kidsleft = 0;				/* <<< Added */

/* format_num --- helper function since can't use [sf]printf() */

const char *format_num(int num)
{
#define NUMSIZ	30
	static char buf[NUMSIZ];
	int i;

	if (num <= 0) {
		strcpy(buf, "0");
		return buf;
	}

	i = NUMSIZ - 1;
	buf[i--] = '\0';

	/* Generate digits backwards into string. */
	do {
		buf[i--] = (num % 10) + '0';
		num /= 10;
	} while (num > 0);

	return & buf[i+1];
}

/* childhandler --- catch SIGCHLD, reap all available children */

void childhandler(int sig)
{
	int status, ret;
	int i;
	char buf[100];
	static const char entered[] = "Entered childhandler\n";
	static const char exited[] = "Exited childhandler\n";

	write(1, entered, strlen(entered));
	for (i = 0; i < nkids; i++) {
		if (kids[i] == NOT_USED)
			continue;

	retry:
		if ((ret = waitpid(kids[i], & status, WNOHANG)) == kids[i]) {
			strcpy(buf, "\treaped process ");
			strcat(buf, format_num(ret));
			strcat(buf, "\n");
			write(1, buf, strlen(buf));
			kids[i] = NOT_USED;
			kidsleft--;			/* <<< Added */
		} else if (ret == 0) {
			strcpy(buf, "\tpid ");
			strcat(buf, format_num(kids[i]));
			strcat(buf, " not available yet\n");
			write(1, buf, strlen(buf));
		} else if (ret == -1 && errno == EINTR) {
			write(1, "\tretrying\n", 10);
			goto retry;
		} else {
			strcpy(buf, "\twaitpid() failed: ");
			strcat(buf, strerror(errno));
			strcat(buf, "\n");
			write(1, buf, strlen(buf));
		}
	}
	write(1, exited, strlen(exited));
}

/* main --- set up child-related information and signals, create children */

int main(int argc, char **argv)
{
	struct sigaction sa;
	sigset_t childset, emptyset;
	int i;

	for (i = 0; i < nkids; i++)
		kids[i] = NOT_USED;

	sigemptyset(& emptyset);

	sa.sa_flags = SA_NOCLDSTOP;
	sa.sa_handler = childhandler;
	sigfillset(& sa.sa_mask);	/* block everything when handler runs */
	sigaction(SIGCHLD, & sa, NULL);

	sigemptyset(& childset);
	sigaddset(& childset, SIGCHLD);

/*	sigprocmask(SIG_SETMASK, & childset, NULL);	/* block it in main code */

	for (nkids = 0; nkids < 5; nkids++) {
		if ((kids[nkids] = fork()) == 0) {
			sleep(3);
			_exit(0);
		}
		kidsleft++;		/* <<< Added */
	}

/*	sleep(5);	/* give the kids a chance to terminate */

	while (kidsleft > 0) {		/* <<< Added */
		printf("waiting for signals\n");
		sigsuspend(& emptyset);
	}				/* <<< Added */

	return 0;
}
