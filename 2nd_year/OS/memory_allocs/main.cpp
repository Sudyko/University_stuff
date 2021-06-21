#include <fstream>
#include <iostream>
#include <chrono>
#include <Windows.h>

void* CallAllocs(int n, char type) {
	switch (type) {
	case 0:
		return malloc(sizeof(int) * n);
		break;
	case 1:
		return new int[n];
		break;
	case 2:
		return VirtualAlloc(NULL, n, MEM_COMMIT,
			PAGE_READWRITE);
		break;
	}
	return NULL;
}

void CallFrees(void* mem, char type) {
	switch (type) {
	case 0:
		free(mem);
		break;
	case 1:
		delete mem;
		break;
	case 2:
		VirtualFree(mem, 0, MEM_RELEASE);
		break;
	}
	return;
}

int main() {
	int n = 1;
	std::ofstream ofile;
	ofile.open("data.txt");
	while (n < 10000000) {
		ofile << n;
		for (uint8_t i = 0; i < 3; ++i) {
			auto start = std::chrono::high_resolution_clock::now();
			auto buffer = CallAllocs(n, i);
			CallFrees(buffer, i);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<
				std::chrono::microseconds>(stop - start);
			ofile << ";" << duration.count();
		}
		ofile << std::endl;
		n += 10000;
	}
	ofile.close();
	return 0;
}