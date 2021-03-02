#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	int memp = SystemInfo.dwPageSize;
	void *mem;
	while(1) {
		mem = VirtualAlloc(NULL, memp, MEM_COMMIT, PAGE_READWRITE);
		memset(mem, 0, memp);
	}
	return 0;
}
