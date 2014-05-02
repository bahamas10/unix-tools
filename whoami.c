/**
 * print stuff to the terminal
 *
 * Author: Dave Eddy <dave@daveeddy.com>
 * Date: 4/9/2013
 * License: MIT
 */

#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <uuid/uuid.h>

int main() {
	struct passwd *p;
	if (!(p = getpwuid(getuid())))
		return 1;

	printf("name\t%s\n", p->pw_name);
	printf("passwd\t%s\n", p->pw_passwd);
	printf("uid\t%d\n", p->pw_uid);
	printf("gid\t%d\n", p->pw_gid);
	printf("gecos\t%s\n", p->pw_gecos);
	printf("dir\t%s\n", p->pw_dir);
	return 0;
}
