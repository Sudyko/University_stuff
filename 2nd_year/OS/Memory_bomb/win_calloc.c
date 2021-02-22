#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	long memp = SystemInfo.dwPageSize;
	while(1) {
		char* mem = (char*)calloc(sizeof(char), memp);
	}
	return 0;
}