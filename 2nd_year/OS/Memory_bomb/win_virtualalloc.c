#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	long memp = SystemInfo.dwPageSize;
	while(1) {
		void *mem = VirtualAlloc(NULL, memp, MEM_COMMIT, PAGE_NOACCESS);
	}
	return 0;
}
