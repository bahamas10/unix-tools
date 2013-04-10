/**
 * env
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/9/2013
 * License: MIT
 */

#include <stdio.h>

void usage();

extern char **environ;

int main(int argc, char **argv) {
	if (argc > 1) {
		usage(0);
		return 1;
	}
	while (*environ != NULL) {
		printf("%s\n", *environ);
		environ++;
	}
	return 0;
}

void usage() {
	fprintf(stderr, "Usage: env\n");
}
