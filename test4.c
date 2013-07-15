#include <linux/unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("There must be a process id given for zombify to work\n");
		return -1;
	}
	long arg = atol(argv[1]);
	syscall(286,arg);
	return 0;
}
