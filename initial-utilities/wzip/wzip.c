#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	char c;
	char lastchar;
	int counter = 0; // counter ASCII code numbers.
	for (int i = 1; i < argc; i++) {
		FILE* fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wzip: can not open the file\n");
			exit(1);
		}
		while ((c = (char) fgetc(fp)) != EOF) { // I didn't realize 'fgetc' is useful here at once. Simply remember this trick.
			if (counter == 0) {
				lastchar = c;
				counter++;
			} else if (c == lastchar) {
				counter++;
			} else {
				fwrite(&counter, 4, 1, stdout);
				fwrite(&lastchar, 1, 1, stdout);
				lastchar = c;
				counter = 1;
			}
		}
		fclose(fp);
	}
	fwrite(&counter, 4, 1, stdout);
	fwrite(&lastchar, 1, 1, stdout);
	
	return 0;
}

