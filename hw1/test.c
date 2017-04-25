#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
int main(){
	syscall(338);
	//printf("multiply(12,25)=%ld \n", syscall(339, 12, 25));
	//printf("min(35,12)=%ld\n", syscall(341, 35, 12));
	//syscall(342);
	return 0;
}

