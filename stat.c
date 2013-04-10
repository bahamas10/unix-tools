/**
 * stat files and print info
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/8/13
 * License: MIT
 */

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define TIME_FMT "%m/%d/%y-%I:%M:%S"
#define TIME_LEN 18

int dostat();
void usage();

int main(int argc, char **argv) {
	int c; // getopt
	int i; // argument loop
	int ret = 0; // return code

	if (argc < 2) {
		usage();
		return 1;
	}

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

	// loop the remaining arguments and print them
	for (i = optind; i < argc; i++) {
		ret += dostat(argv[i]);
	}
	return ret;
}

/**
 * stat a given file and print info about it
 *
 * returns 0 for success, 1 for failure
 */
int dostat(const char *fname) {
	char dbuf[TIME_LEN];
	struct stat sb; // stat buffer
	if (lstat(fname, &sb) == -1) {
		perror(fname);
		return 1;
	}

	printf("-- %s --\n", fname);
	printf("type: ");
	switch (sb.st_mode & S_IFMT) {
		case S_IFIFO: printf("named pipe (fifo)\n"); break;
		case S_IFCHR: printf("character special\n"); break;
		case S_IFDIR: printf("directory\n"); break;
		case S_IFBLK: printf("block special\n"); break;
		case S_IFREG: printf("regular file\n"); break;
		case S_IFLNK: printf("symbolic link\n"); break;
		case S_IFSOCK: printf("socket\n"); break;
#ifdef S_IFWHT
		case S_IFWHT: printf("whiteout\n"); break;
#endif
		default: printf("unknown filetype\n"); break;
	}
	printf("size: %d bytes\n", (int)sb.st_size);
	printf("uid: %d\n", sb.st_uid);
	printf("gid: %d\n", sb.st_gid);
	printf("mode: %o\n", sb.st_mode);
	printf("inode: %d\n", (int)sb.st_ino);

	if (strftime(dbuf, TIME_LEN, TIME_FMT, localtime(&sb.st_mtime)))
		printf("mtime: %s\n", dbuf);
	if (strftime(dbuf, TIME_LEN, TIME_FMT, localtime(&sb.st_atime)))
		printf("atime: %s\n", dbuf);
	if (strftime(dbuf, TIME_LEN, TIME_FMT, localtime(&sb.st_ctime)))
		printf("ctime: %s\n", dbuf);

	return 0;
}

void usage() {
	fprintf(stderr, "usage: stat file ...\n");
}
