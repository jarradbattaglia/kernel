#include <linux/unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	long arg = atol(argv[1]);
	syscall(286,arg);
	return 0;
}
