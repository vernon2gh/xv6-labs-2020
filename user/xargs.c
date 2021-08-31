#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char **argv)
{
	char *cmd;
	char *arg[MAXARG];
	int pos = 0;
	char line_buf[1024];
	int i, head = 0, next = 0;

	cmd = argv[1];

	for(i=1; i<argc; i++) {
		arg[pos++] = argv[i];
	}

	while(read(0, (line_buf + next), sizeof(char)) > 0) {
		if((line_buf[next] == ' ') || (line_buf[next] == '\n')) {
			line_buf[next] = '\0';
			arg[pos++] = (line_buf + head);
			head = next + 1;
		}
		next++;
	}

	if (fork() == 0) {
		exec(cmd, arg);
	} else {
		wait(0);
	}

	exit(0);
}
