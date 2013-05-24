/* ch09-atexit.c --- demonstrate atexit().
		     Error checking omitted for brevity. */

/*
 * The callback functions here just answer roll call.
 * In a real application, they would do more.
 */

void callback1(void) { printf("callback1 called\n"); }
void callback2(void) { printf("callback2 called\n"); }
void callback3(void) { printf("callback3 called\n"); }

/* main --- register functions and then exit */

int main(int argc, char **argv)
{
	printf("registering callback1\n");	atexit(callback1);
	printf("registering callback2\n");	atexit(callback2);
	printf("registering callback3\n");	atexit(callback3);

	printf("exiting now\n");
	exit(0);
}
