#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	long memp = getpagesize();
	while(1) {
		char* mem = (char*)calloc(sizeof(char), memp);
	}
	return 0;
}
// OOM killer AK Out-Of-Memory Killer helps you.