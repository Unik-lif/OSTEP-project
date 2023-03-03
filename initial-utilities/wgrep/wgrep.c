#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	if (argc == 2) {
		size_t n = 0;
		char* buf;
		while (getline(&buf, &n, stdin) != -1) {
			if (strstr(buf, argv[1]) != NULL)
				printf("%s", buf);	
			memset(buf, 0, n);
		}
		return 0;
	}
	for (int i = 2; i < argc; i++) {
		size_t n = 0;
		char* buf;
		FILE* fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wgrep: cannot open file\n");
			exit(1);
		}
		while (getline(&buf, &n, fp) != -1) {
			if (strstr(buf, argv[1]) != NULL) 
				printf("%s", buf);
			memset(buf, 0, n);
		}
	}
	return 0;
}
