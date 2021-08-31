#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
	unsigned int seconds;

	if(argc != 2) {
		printf("usage: %s <second>\n", argv[0]);
		exit(1);
	}

	seconds = atoi(argv[1]);
	sleep(seconds);

	exit(0);
}
