#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int judge(char *a, char *b, int len);

int main(int argc, char *argv[]) {
	
	if (argc == 1 || argc > 3) {
		printf("bad input\n");
		exit(-1);	
	}
	
	char buffer[256] = {0};  
	FILE* fp = NULL;
	if (argc == 2)
		fp = fopen("/usr/share/dict/words", "r");
	else 
		fp = fopen(argv[2], "r");
	if (fp == NULL) {
		printf("fail to open the file %s\n", argv[2]);
		exit(1);
	}
	while (!feof(fp)) {
		fgets(buffer, 256, fp);
		if (judge(argv[1], buffer, strlen(argv[1]))) 
			printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
	fclose(fp);
}
// judge whether we can print it out.
int judge(char *a, char *b, int len) {
	for (int i = 0; i < len; i++) {
		if ((a[i] != b[i]) && (toupper(a[i]) != toupper(b[i]))) {
			return 0;
		}
	}
	return 1;
}
