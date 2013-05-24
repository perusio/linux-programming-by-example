/* ch13-echodate.c --- demonstrate translations */

#include <stdio.h>
#include <time.h>
#include <locale.h>
#define ENABLE_NLS 1
#include "gettext.h"
#define _(msgid) gettext(msgid)
#define N_(msgid) msgid

int main(void)
{
	struct tm tm;
	time_t then;

	setlocale(LC_ALL, "");
	bindtextdomain("echodate", ".");
	textdomain("echodate");

	printf("%s", _("Enter a Date/time as YYYY/MM/DD HH:MM:SS : "));
	scanf("%d/%d/%d %d:%d:%d",
		& tm.tm_year, & tm.tm_mon, & tm.tm_mday,
		& tm.tm_hour, & tm.tm_min, & tm.tm_sec);

	/* Error checking on values omitted for brevity. */
	tm.tm_year -= 1900;
	tm.tm_mon -= 1;

	tm.tm_isdst = -1;	/* Don't know about DST */

	then = mktime(& tm);

	printf(_("Got: %s"), ctime(& then));
	exit(0);
}
