/**
 * print stuff to the terminal
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/9/2013
 * License: MIT
 */

#include <stdio.h>
#include <unistd.h>

void usage();

int main(int argc, char **argv) {
	int c; // getopt
	int i; // argument loop

	int newline = 1;
	while ((c = getopt(argc, argv, "hn")) != EOF) {
		switch (c) {
			case 'h':
				usage();
				return 0;
			case 'n':
				newline = 0;
				break;
			case '?':
				usage();
				return 1;
		}
	}

	// loop the remaining arguments and print them
	for (i = optind; i < argc; i++) {
		printf("%s", argv[i]);
		if (i < argc - 1) putchar(' ');
	}
	if (newline) putchar('\n');
	return 0;
}

void usage() {
	fprintf(stderr, "Usage: echo [-h] [-n] [string ...]\n");
}
