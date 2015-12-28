/**
 * print a file to stdout
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 5/1/2014
 * License: MIT
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void pipefd(int, int);

int main(int argc, char **argv) {
	int fd;
	int ret = 0;
	int i;

	if (argc <= 1) {
		// pipe stdin to stdout
		pipefd(0, 1);
		return 0;
	}

	// loop the arguments
	for (i = 1; i < argc; i++) {
		// open the file
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
			fprintf(stderr, "open %s: %s\n", argv[i], strerror(errno));
			ret = 1;
			continue;
		}

		// hook the fd to stdout and read it
		pipefd(fd, 1);

		// close the file
		close(fd);
	}

	return ret;
}

void pipefd(int inputfd, int outputfd) {
	char buf[BUFSIZ];
	int bytesread = 0;
	while ((bytesread = read(inputfd, buf, BUFSIZ)) > 0)
		write(outputfd, buf, bytesread);
}
