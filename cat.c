#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BLOCK_SIZE 512

void pipefile(int, int);

int main(int argc, char **argv) {
	if (argc <= 1) {
		// pipe stdin to stdout
		pipefile(0, 1);
		return 0;
	}

	// loop the arguments
	int fd;
	int ret = 0;
	for (int i = 1; i < argc; i++) {
		// open the file
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
			fprintf(stderr, "open %s: %s\n", argv[i], strerror(errno));
			ret++;
		}

		// hook the fd to stdout and read it
		pipefile(fd, 1);

		// close the file
		close(fd);
	}

	return ret;
}

void pipefile(int inputfd, int outputfd) {
	char buf[BLOCK_SIZE];
	int bytesread = 0;
	while ((bytesread = read(inputfd, buf, BLOCK_SIZE)) > 0)
		write(outputfd, buf, bytesread);
}
