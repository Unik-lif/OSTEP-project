#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

bool are_files_different(const char* file1, const char* file2) {
    struct stat stat1, stat2;
    if (stat(file1, &stat1) != 0 || stat(file2, &stat2) != 0) {
        // Error occurred while reading file stats
        return true;
    }
    if (stat1.st_ino != stat2.st_ino || stat1.st_dev != stat2.st_dev || stat1.st_size != stat2.st_size) {
        // Files are different
        return true;
    }
    // Files are the same
    return false;
}

int main(int argc, char* argv[]) {
	int init_len = 16;
	int true_len = 0;
	size_t n = 0;
	char* buf;
	FILE* fp = NULL;
	FILE* fq = NULL;
	
	// cases for fp & fq, with error checks.
	if (argc == 1) {
		fp = stdin;
		fq = stdout;
	}
	else if (argc == 2 || argc == 3) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);	
		}
		if (argc == 2)
			fq = stdout;
		else {
			if (strcmp(argv[2], argv[1]) == 0) {
				fprintf(stderr, "reverse: input and output file must differ\n");
				exit(1);
			}
			if (are_files_different(argv[1], argv[2]) == false) {
				fprintf(stderr, "reverse: input and output file must differ\n");
				exit(1);
			}
			fq = fopen(argv[2], "w");
			if (fq == NULL) {
				fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
				exit(1);	
			}
		}
	} else {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}

	// temporaty storing position.
	char** file = (char **) malloc (sizeof(char *) * 16);
	if (file == NULL) {
		fprintf(stderr, "fail to malloc\n");
		exit(1);
	}
	for (int i = 0; getline(&buf, &n, fp) != -1; i++) {
		if (i >= init_len) {
			init_len *= 2;
			file = (char **) realloc (file, sizeof(char *) * init_len);
			if (file == NULL) {
				fprintf(stderr, "fail to realloc\n");
				exit(1);
			}
		}
		file[i] = (char*) malloc (n);
		memset(file[i], 0, n);
		strncpy(file[i], buf, n);
			
		memset(buf, 0, n);
		n = 0;
		true_len++;
	}
	for (int i = true_len - 1; i >= 0; i--) {
		fputs(file[i], fq);
	}
	fclose(fp);
	fclose(fq);
	return 0;
}
