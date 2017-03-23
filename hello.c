#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
int main(){
	syscall(337);
	return 0;
}
