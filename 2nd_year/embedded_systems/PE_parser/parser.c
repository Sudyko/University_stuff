#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc != 2) return 2;
	FILE* fin;
	FILE* fout;
	FILE* bfout;
	fin = fopen(argv[argc - 1], "rb");
	if(fin == NULL) return 2;
	fout = fopen("sections.txt", "w");
	if(fout == NULL){
		fclose(fin);
		return 2;
	}
	bfout = fopen("code.txt", "wb");
	if(bfout == NULL){
		fclose(fin);
		fclose(fout);
		return 2;
	}
	char check[3];
	check[2] = '\0';
	fread(check, sizeof(char), 2, fin);
	if(strcmp(check, "MZ")) {
		fclose(fin);
		fclose(fout);
		fclose(bfout);
		return 3;
	}
	fseek(fin, 58, SEEK_CUR);
	size_t lfanew = 0, size_of_opt_h = 0;
	fread(&lfanew, 4, 1, fin); // offset of the PE-header
	printf("%d", lfanew);
	fseek(fin, lfanew, SEEK_SET);
	fread(check, sizeof(char), 2, fin);
	if (strcmp(check, "PE")) {
		fclose(fin);
		fclose(fout);
		fclose(bfout);
		return 3;
	}
	fseek(fin, 4, SEEK_CUR);
	int num_of_sec = 0;
	fread(&num_of_sec, 2, 1, fin); // Number of sections
	fseek(fin, 12, SEEK_CUR);
	fread(&size_of_opt_h, 2, 1, fin); // Size of optional header (relative offset of the section table)
	fseek(fin, 18, SEEK_CUR);
	size_t ep = 0;
	fread(&ep, 4, 1, fin); // Address of entry point
	fprintf(fout, "Entry point: %x\n\n", ep);
	fseek(fin, size_of_opt_h - 20, SEEK_CUR);
	char sec[9];
	sec[8] = '\0';
	size_of_opt_h += lfanew + 24;
	for (int i = 0; i < num_of_sec; ++i) {
		size_t vs, va, rs, ra;
		fread(sec, sizeof(char), 8, fin);
		fputs(sec, fout);
		fputs("\n", fout);
		fread(&vs, 4, 1, fin); // Virtual size
		fread(&va, 4, 1, fin); // Virtual address
		fread(&rs, 4, 1, fin); // Size of raw data
		fread(&ra, 4, 1, fin); // Pointer to raw data
		fprintf(fout, "Virtual size: %x\nVirtual address: %x\nSize of raw data: %x\nPointer to raw data: %x\n", vs, va, rs, ra);
		fseek(fin, 12, SEEK_CUR);
		fread(&ep, 4, 1, fin); // Characteristics
		fputs("Characteristics:\n", fout);
		if (ep & 0x20) {
			fputs("Code flag\n", fout);
			char* buf = (char*)malloc(rs);
			fseek(fin, ra, SEEK_SET);
			fread(buf, 1, rs, fin);
			fwrite(buf, 1, rs, bfout);
			free(buf);
			fseek(fin, size_of_opt_h + (40 * (i + 1)), SEEK_SET);
		}
		if (ep & 0x40) fputs("Initialized data flag\n", fout);
		if (ep & 0x80) fputs("Uninitialized data flag\n", fout);
		if (ep & 0x200) fputs("Comments flag\n", fout);
		if (ep & 0x800) fputs("Not for .exe flag\n", fout);
		if (ep & 0x2000000) fputs("Discarded flag\n", fout);
		if (ep & 0x10000000) fputs("Shared flag\n", fout);
		if (ep & 0x20000000) fputs("Executable flag\n", fout);
		if (ep & 0x40000000) fputs("Read flag\n", fout);
		if (ep & 0x80000000) fputs("Write flag\n", fout);
		fputs("\n", fout);
	}
	fclose(fin);
	fclose(fout);
	fclose(bfout);
	return 0;
}
