#include "notify.h"

int notify_callback(int param)
{
	printf("key = %d\n", param);

	return 0;
}

int main(int argc, char *argv[])
{
	printf("Register callback to notify\n");
	notify_register(1, 1, notify_callback);
	return 0;
}