#include <linux/unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	long arg = atol(argv[1]);
	printf("TimeSlice: %d\n", syscall(287,arg));
	return 0;
}
