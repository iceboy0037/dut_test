#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "notify.h"

int notify_callback(int param)
{
	printf("key = %d\n", param);

	return 0;
}

int server(void)
{
	char c;

	notify_init(NOTIFY_SERVER);
	while (1) {
		c = getchar();
		switch (c) {
		case 's':
			notify_send(0);
			break;
		case 'q':
			exit(0);
		default:
			break;
		}
	}
	return 0;
}
int client(void)
{
	notify_init(NOTIFY_CLIENT);
	printf("Register callback to notify\n");
	for (int i = 0; i < 10; i++) {
		notify_register(1, i, notify_callback, i);
	}
	notify_print_list();
	while (1) {
		sleep(1);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		println("\nusage: notify <opt>\n");
		println("\ts\t- Server\n");
		println("\tc\t- Client\n");
		return -1;
	}

	if (argv[1][0] == 's') {
		server();
	} else {
		client();
	}
	return 0;
}