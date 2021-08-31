#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void path_file(char *buf, char *path, char *file)
{
	int offse, size;

	offse = strlen(path);
	size = strlen(file);

	strcpy(buf, path);
	buf[offse++] = '/';
	while(size--) {
		buf[offse++] = *file++;
	}
	buf[offse] = '\0';
}

void find(char *path, char *file)
{
	int fd;
	struct dirent directory;
	struct stat state;
	char buf[1024];

	fd = open(path, 0);

	while(read(fd, &directory, sizeof(directory)) && strcmp(directory.name, "")) {
		if((!strcmp(directory.name, ".")) || (!strcmp(directory.name, "..")))
			continue;

		path_file(buf, path, directory.name);
		stat(buf, &state);

		switch(state.type) {
		case T_FILE:
			if(!strcmp(directory.name, file))
				printf("%s\n", buf);
			break;
		
		case T_DIR:
			find(buf, file);
			break;

		default:
			break;
		}
	}
}

int main(int argc, char **argv)
{
	char *path, *file;

	if(argc != 3) {
		printf("usage: %s [path] [file]\n", argv[0]);
		exit(1);
	}

	path = argv[1];
	file = argv[2];
	find(path, file);

	exit(0);
}
