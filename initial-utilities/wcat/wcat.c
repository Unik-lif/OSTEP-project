#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	// judget whether the wcat is success or not.	
	int flag = 0;
	for (int i = 1; i < argc; i++) {
		char buff[256] = {0};
		FILE* file = fopen(argv[i], "r");
		if (file == NULL) {
			printf("wcat: cannot open file\n");
			exit(1);
		}
		flag = 1;
		while (!feof(file)) {
			fgets(buff, 256, file);
			printf("%s", buff);
			memset(buff, 0, 256);
		}
		fclose(file);
	}
	if (flag == 0) {
		exit(0);
	}
	return 0;
}
