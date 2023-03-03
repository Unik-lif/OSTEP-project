#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}
	int num;
	char ch;
	for (int i = 1; i < argc; i++) {
		FILE* fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("fail to open the file\n");
			exit(1);
		}
		while (!feof(fp)) {
			fread(&num, 4, 1, fp);
			fread(&ch, 1, 1, fp);
			for (int i = 0; i < num; i++)
				printf("%c", ch);
			num = 0;
			ch = 0;
		}
		fclose(fp);
	}
	return 0;
}
