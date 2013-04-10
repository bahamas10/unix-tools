/**
 * hostname
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/9/2013
 * License: MIT
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 255
#endif

void usage();

int main(int argc, char **argv) {
	char buf[MAXHOSTNAMELEN + 1];
	buf[MAXHOSTNAMELEN] = '\0'; // ensure termination

	if (argc > 1) {
		usage();
		return 1;
	}

	if (gethostname(buf, MAXHOSTNAMELEN) == -1) {
		perror("gethostname");
		return 1;
	}

	printf("%s\n", buf);
	return 0;
}

void usage() {
	fprintf(stderr, "Usage: hostname\n\nget the systems hostname\n");
}
