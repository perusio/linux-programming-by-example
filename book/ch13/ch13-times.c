/* ch13-times.c --- demonstrate locale-based times */

#include <stdio.h>
#include <locale.h>
#include <time.h>

int main(void)
{
	char buf[100];
	time_t now;
	struct tm *curtime;

	setlocale(LC_ALL, "");
	time(& now);
	curtime = localtime(& now);
	(void) strftime(buf, sizeof buf,
			"It is now %A, %B %d, %Y, %I:%M %p", curtime);

	printf("%s\n", buf);

	printf("ctime() says: %s", ctime(& now));
	exit(0);
}
