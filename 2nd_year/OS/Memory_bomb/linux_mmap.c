#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
	long memp = getpagesize();
	while(1) {
		void *mem = mmap(NULL, memp, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	}
	return 0;
}
