/* ch06-echodate.c --- demonstrate mktime(). */

#include <stdio.h>
#include <time.h>

int main(void)
{
	struct tm tm;
	time_t then;

	printf("Enter a Date/time as YYYY/MM/DD HH:MM:SS : ");
	scanf("%d/%d/%d %d:%d:%d",
		& tm.tm_year, & tm.tm_mon, & tm.tm_mday,
		& tm.tm_hour, & tm.tm_min, & tm.tm_sec);

	/* Error checking on values omitted for brevity. */
	tm.tm_year -= 1900;
	tm.tm_mon--;

	tm.tm_isdst = -1;	/* Don't know about DST */

	then = mktime(& tm);

	printf("Got: %s", ctime(& then));
	exit(0);
}
