/**
 * uname clone
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/10/2013
 * License: MIT
 */

#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

void usage();

int main(int argc, char **argv) {
	struct utsname buf;
	int c;

	while ((c = getopt(argc, argv, "h")) != EOF) {
		switch (c) {
			case 'h':
				usage();
				return 0;
			case '?':
				usage();
				return 1;
		}
	}

	// call uname(2)
	if (uname(&buf) == -1) {
		perror("uname(2)");
		return 1;
	}

	printf("%s\n", buf.machine);
	return 0;
}

void usage() {
	fprintf(stderr, "Usage: arch [-h]\n");
}
