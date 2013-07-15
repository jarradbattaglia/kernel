#include <linux/unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("There should be two arguments target and victim");
		return -1;
	}
	long arg1 = atol(argv[1]);
	long arg2 = atol(argv[2]);
	printf("Timeslice for target: %d\n", syscall(288,arg1, arg2));
	return 0;
}
