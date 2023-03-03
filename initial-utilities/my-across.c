#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int judge(char *a, char *b);

int main(int argc, char *argv[]) {
	
	if (argc != 4) {
		printf("bad input\n");
		exit(-1);	
	}

	if (strlen(argv[1]) + atoi(argv[2]) > atoi(argv[3])) {
		printf("Invalid\n");
		exit(-1);
	}
	char buffer[256] = {0};  
	FILE* fp = NULL;
	fp = fopen("/usr/share/dict/words", "r");
	if (fp == NULL) {
		printf("fail to open the file %s\n", argv[2]);
		exit(1);
	}

	while (!feof(fp)) {
		fgets(buffer, 256, fp);
		if (judge(argv[1], buffer + atoi(argv[2])) && strlen(buffer) - 1 == atoi(argv[3])) 
			printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
	fclose(fp);
}
// judge whether we can print it out.
int judge(char *a, char *b) {
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}
