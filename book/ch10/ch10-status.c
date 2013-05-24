/* ch10-status.c --- demonstrate SIGCHLD management, use 3 argument handler */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void manage(siginfo_t *si);

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

/* childhandler --- catch SIGCHLD, reap just one child */

void childhandler(int sig, siginfo_t *si, void *context)
{
	int status, ret;
	int i;
	char buf[100];
	static const char entered[] = "Entered childhandler\n";
	static const char exited[] = "Exited childhandler\n";

	write(1, entered, strlen(entered));
retry:
	if ((ret = waitpid(si->si_pid, & status, WNOHANG)) == si->si_pid) {
		strcpy(buf, "\treaped process ");
		strcat(buf, format_num(si->si_pid));
		strcat(buf, "\n");
		write(1, buf, strlen(buf));
		manage(si);			/* deal with what happened to it */
	} else if (ret > 0) {
		strcpy(buf, "\treaped unexpected pid ");
		strcat(buf, format_num(ret));
		strcat(buf, "\n");
		write(1, buf, strlen(buf));
		goto retry;		/* why not? */
	} else if (ret == 0) {
		strcpy(buf, "\tpid ");
		strcat(buf, format_num(si->si_pid));
		strcat(buf, " changed status\n");
		write(1, buf, strlen(buf));
		manage(si);			/* deal with what happened to it */
	} else if (ret == -1 && errno == EINTR) {
		write(1, "\tretrying\n", 10);
		goto retry;
	} else {
		strcpy(buf, "\twaitpid() failed: ");
		strcat(buf, strerror(errno));
		strcat(buf, "\n");
		write(1, buf, strlen(buf));
	}

	write(1, exited, strlen(exited));
}

/* child --- what to do in the child */

void child(void)
{
	raise(SIGCONT);		/* should be ignored */
	raise(SIGSTOP);		/* go to sleep, parent wakes us back up */
	printf("\t---> child restarted <---\n");
	exit(42);		/* normal exit, let parent get value */
}

/* main --- set up child-related information and signals, create child */

int main(int argc, char **argv)
{
	pid_t kid;
	struct sigaction sa;
	sigset_t childset, emptyset;

	sigemptyset(& emptyset);

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = childhandler;
	sigfillset(& sa.sa_mask);	/* block everything when handler runs */
	sigaction(SIGCHLD, & sa, NULL);

	sigemptyset(& childset);
	sigaddset(& childset, SIGCHLD);

	sigprocmask(SIG_SETMASK, & childset, NULL);	/* block it in main code */

	if ((kid = fork()) == 0)
		child();

	/* parent executes here */
	for (;;) {
		printf("waiting for signals\n");
		sigsuspend(& emptyset);
	}

	return 0;
}

/* manage --- deal with different things that could happen to child */

void manage(siginfo_t *si)
{
	char buf[100];

	switch (si->si_code) {	
	case CLD_STOPPED:
		write(1, "\tchild stopped, restarting\n", 27);
		kill(si->si_pid, SIGCONT);
		break;

	case CLD_CONTINUED:	/* not sent on Linux */
		write(1, "\tchild continued\n", 17);
		break;

	case CLD_EXITED:
		strcpy(buf, "\tchild exited with status ");
		strcat(buf, format_num(si->si_status));
		strcat(buf, "\n");
		write(1, buf, strlen(buf));
		exit(0);	/* we're done */
		break;
	
	case CLD_DUMPED:
		write(1, "\tchild dumped\n", 14);
		break;

	case CLD_KILLED:
		write(1, "\tchild killed\n", 14);
		break;

	case CLD_TRAPPED:
		write(1, "\tchild trapped\n", 15);
		break;
	}
}
