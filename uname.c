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

	int machine = 0;
	int nodename = 0;
	int release = 0;
	int sysname = 0;
	int version = 0;
	int c;
	while ((c = getopt(argc, argv, "ahmnrsv")) != EOF) {
		switch (c) {
			case 'a':
				machine = 1;
				nodename = 1;
				release = 1;
				sysname = 1;
				version = 1;
				break;
			case 'h':
				usage();
				return 0;
			case 'm':
				machine = 1;
				break;
			case 'n':
				nodename = 1;
				break;
			case 'r':
				release = 1;
				break;
			case 's':
				sysname = 1;
				break;
			case 'v':
				version = 1;
				break;
			case '?':
				usage();
				return 1;
		}
	}
	if (argc == 1) sysname = 1;

	// call uname(2)
	if (uname(&buf) == -1) {
		perror("uname(2)");
		return 1;
	}

	if (sysname) printf("%s\n", buf.sysname);
	if (nodename) printf("%s\n", buf.nodename);
	if (release) printf("%s\n", buf.release);
	if (version) printf("%s\n", buf.version);
	if (machine) printf("%s\n", buf.machine);

	return 0;
}

void usage() {
	fprintf(stderr, "Usage: uname [-r] [-a] [-n] [-s] [-v] [-m]\n");
}
