#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// first, we need to implement LCS algorithm
void LCS(char** a, char** b, int alen, int blen, unsigned char** grid) {
	for (int i = 0; i < alen + 1; i++)
		grid[i][0] = 0;
	for (int j = 0; j < blen + 1; j++)
		grid[0][j] = 0;
	
	for (int i = 0; i < alen; i++) {
		for (int j = 0; j < blen; j++) {
			if (strcmp(a[i], b[j]) == 0) 
				grid[i + 1][j + 1] = 1 + grid[i][j];
			else
				grid[i + 1][j + 1] = grid[i][j + 1] > grid[i + 1][j]? grid[i][j + 1]: grid[i + 1][j];
		}
	}
	
}
// second, recursively print_diff to get the result.
void print_diff(unsigned char** grid, char* a[], char* b[], int lefta, int leftb) {
	if (lefta > 0 && leftb > 0 && strcmp(a[lefta - 1], b[leftb - 1]) == 0) {
		print_diff(grid, a, b, lefta - 1, leftb - 1);
		printf("%s", a[lefta - 1]);
	} else if (leftb > 0 && (lefta == 0 || grid[lefta][leftb - 1] >= grid[lefta - 1][leftb])) {
		print_diff(grid, a, b, lefta, leftb - 1);
		printf("> %s", b[leftb- 1]);
	} else if (lefta > 0 && (leftb == 0 || grid[lefta - 1][leftb] >= grid[lefta][leftb - 1])) {
		print_diff(grid, a, b, lefta - 1, leftb);
		printf("< %s", a[lefta - 1]);
	} else {
		printf("");
	}
}

// we divide the tasks into multi tiny steps.
// LCS -> fetch every line for the algorithm to be conducted.
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Invalid arguments number!\n");
		exit(1);
	}
	FILE* fp = fopen(argv[1], "r");
	FILE* fq = fopen(argv[2], "r");
	if (fp == NULL || fq == NULL) {
		printf("fail to open the file to be compared\n");
		exit(2);
	}
	char **afile = (char **) malloc (sizeof(char *) * 128);
	for (int i = 0; i < 128; i++) {
		afile[i] = (char *) malloc (sizeof(char) * 128);
		memset(afile[i], 0, 128);
	}
	char **bfile = (char **) malloc (sizeof(char *) * 128);
	for (int i = 0; i < 128; i++) {
		bfile[i] = (char *) malloc (sizeof(char) * 128);
		memset(bfile[i], 0, 128);
	}
	// buf size: 256, which will be automatically adjust due to getline functions.
	int alen = 0;
	int blen = 0;
	size_t size = 0;
	char *abuf;
	char *bbuf;
	while (getline(&abuf, &size, fp) != -1) {
		strncpy(afile[alen], abuf, 256);
		memset(abuf, 0, size);
		alen++;
	}
	
	while (getline(&bbuf, &size, fq) != -1) {
		strncpy(bfile[blen], bbuf, 256);
		memset(bbuf, 0, size);
		blen++;
	}
	printf("alen = %d, blen = %d\n", alen, blen);
	unsigned char ** grid = (unsigned char **) malloc (256 * sizeof(unsigned char *));
	for (int i = 0; i < 256; i++) {
		grid[i] = (unsigned char *) malloc (256);
		memset(grid[i], 0, 256);
	}
	LCS(afile, bfile, alen, blen, grid);
	
	for (int i = 0; i < alen + 1; i++) {
		for (int j = 0; j < blen + 1; j++) 
			printf("%d", grid[i][j]);
		printf("\n");
	}
	
	print_diff(grid, afile, bfile, alen, blen);	
}
