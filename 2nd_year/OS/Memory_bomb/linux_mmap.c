#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
	long memp = getpagesize();
	while(1) {
		void *mem = mmap(NULL, memp, 0, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
		if(mem == MAP_FAILED) { // Catch errors
			perror("mmap");
		}
	}
	return 0;
}
// vim /etc/sysctl.conf
// [change] vm.max_map_count = 1750000 -- максимальное количество областей карты памяти процесса
