#include "notify.h"

int notify_callback(int param)
{
	printf("key = %d\n", param);

	return 0;
}

int main(int argc, char *argv[])
{
	printf("Register callback to notify\n");
	for (int i = 0; i < 10; i++) {
		notify_register(1, i, notify_callback, i);
	}
	notify_print_list();
	return 0;
}