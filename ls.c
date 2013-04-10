/**
 * List files and directories
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/8/13
 * License: MIT
 */

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// functions
void arguments();
void putsafename();
void usage();
int processdir();


// options
struct {
	int all;
	int nul;
	int longls;
} options;

int main(int argc, char **argv) {
	int i; // argument loop
	int ret = 0; // return code

	// command line options
	arguments(argc, argv);

	int multiargs = argc - optind > 1; // more the one operand

	if (optind == argc) {
		// no arguments, assume '.'
		ret += processdir(".");
	} else {
		// loop the operands
		for (i = optind; i < argc; i++) {
			if (multiargs) printf("%s:\n", argv[i]);
			ret += processdir(argv[i]);
			if (multiargs) putchar('\n');
		}
	}
	return ret;
}

// process a directory
int processdir(char *dir) {
	DIR *d; // reusable dirent
	struct dirent *dp; // dir pointer
	// TODO stat(2)

	d = opendir(dir);
	if (d == NULL) {
		perror(dir);
		return 1;
	}

	// loop over the dirent
	while ((dp = readdir(d)) != NULL) {
		if (dp->d_name[0] == '.' && !options.all) continue;
		putsafename(dp->d_name);
		putchar(options.nul ? '\0' : '\n');
	}
	closedir(d);
	return 0;
}

// print a filename safely, escaping \n, \t, etc; must be null terimnated
void putsafename(const char *fname) {
	const char *ptr = fname;
	char c;
	while ((c = *ptr) != '\0') {
		if (c == '\n') printf("\\n");
		else if (c == '\t') printf("\\t");
		else putchar(c);
		ptr++;
	}
}

// process the arguments and set the flags
void arguments(int argc, char **argv) {
	int c;
	while ((c = getopt(argc, argv, "0ahl")) != EOF) {
		switch (c) {
			case '0':
				options.nul = 1;
				break;
			case 'a':
				options.all = 1;
				break;
			case 'h':
				usage();
				exit(0);
			case 'l':
				options.longls = 1;
				break;
			case '?':
				usage();
				exit(1);
		}
	}
}

void usage() {
	fprintf(stderr,
	    "usage: ls [-h] [file ...]\n"
	    "\n"
	    "list files and directories\n"
	    "\n"
	    "options\n"
	    "\n"
	    "  -0    separate file names by the nul byte\n"
	    "  -a    show hidden files as well\n"
	    "  -h    print this message and exit\n"
	);
}
