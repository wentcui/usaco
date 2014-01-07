/*
ID: wentcui1
LANG: C++
TASK: range
*/

#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct node{
	int a;
	int b;
};

int compare(const void* x, const void* y) {
    struct node *nx = (struct node *)x;
    struct node *ny = (struct node *)y;

    return nx->a - ny->a;
}


bool validate1(int matrix[251][251], int row, int f, int t) {
	bool ret = true;
	while(f <= t) {
		if (!matrix[row][f]) {
			ret = false;
			break;
		}
		f++;
	}
	return ret;
}

bool validate2(int matrix[251][251], int col, int f, int t) {
	bool ret = true;
	while(f <= t) {
		if (!matrix[f][col]) {
			ret = false;
			break;
		}
		f++;
	}
	return ret;
}

int main() {
	int i, j, k;
	FILE* fin = fopen("range.in", "r");
	FILE* fout = fopen("range.out", "w");

	int N, pos = 0;
	char c;
	fscanf(fin, "%d", &N);
	int matrix[251][251] = {{0}};
	int dp[251][251] = {{1}};
	int result[251] = {0};
	struct node nodearr[252];

	fgetc(fin);
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			fscanf(fin, "%c", &c);
			matrix[i][j] = c - '0';
		}
		if (i < N)
			fgetc(fin);
	}

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			dp[i][j] = matrix[i][j];
		}
	}
/*
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			printf("%d", matrix[i][j]);
		}
		printf("\n");
	}
*/
	for(k = 2; k <= N; k++)
	for(i = N; i >= k; i--)
	for(j = k; j <= N; j++) {
		if (!matrix[i][j]) {
			dp[i][j] = 0;
			continue;
		}

		//printf("k: %d, i: %d, j: %d, ", k, i, j);
		bool v = dp[i - 1][j - 1] && ((dp[i - 1][j] && dp[i][j - 1]) || (validate1(matrix, i, j - k + 1, j - 1) && validate2(matrix, j, i - k + 1, i - 1)));
		//printf("v1: %d, ", v);
		v |= (dp[i][j - 1] && ((dp[i - 1][j] && dp[i - 1][j - 1]) || (validate1(matrix, i - k + 1, j - k + 1, j - 1) && validate2(matrix, j, i - k + 1, i - 1))));
		//printf("v2: %d, ", v);
		v |= (dp[i - 1][j] && ((dp[i][j - 1] && dp[i - 1][j - 1]) || (validate1(matrix, i, j - k + 1, j - 1) && validate2(matrix, j - k + 1, i - k + 1, i - 1))));
		//printf("v3: %d, ", v);
		v |= (dp[i][j] && matrix[i - k + 1][j - k + 1] && ((dp[i - 1][j] && dp[i][j - 1]) || ((validate1(matrix, i - k + 1, j - k + 2, j) && validate2(matrix, j - k + 1, i - k + 2, i)))));
		//printf("v4: %d\n", v);

		dp[i][j] = v;
		if (v)
			result[k]++;
	}

	for(i = 2; i <= N; i++) {
		if (result[i]) {
			nodearr[pos].a = i;
			nodearr[pos].b = result[i];
			pos++;
		}
	}


	qsort(nodearr, pos, sizeof(struct node), compare);
	for(i = 0; i < pos; i++) {
		fprintf(fout, "%d %d\n", nodearr[i].a, nodearr[i].b);
	}

	fclose(fout);
	fclose(fin);

	return 0;
}
