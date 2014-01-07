/*
ID: wentcui1
LANG: C++
TASK: game1
*/

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
	FILE* fin = fopen("game1.in", "r");
	FILE* fout = fopen("game1.out", "w");

	int n, i, j, k, sum = 0;
	int dp[201][201] = {{0}};
	int arr[201] = {0};
	fscanf(fin, "%d", &n);
	
	for(i = 1; i <= n; i++) {
		fscanf(fin, "%d", &arr[i]);
		sum += arr[i];
	}

	for(i = 1; i <= n; i++) {
		dp[i][i] = arr[i];
		if (i < n)
			dp[i][i + 1] = max(arr[i], arr[i + 1]);
	}
	
	for(k = 3; k <= n; k++) {
		for(i = 1; i <= n - k + 1; i++) {
			j = i + k - 1;
			dp[i][j] = max(arr[i] + min(dp[i + 1][j - 1], dp[i + 2][j]), arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2]));
		}
	}

	fprintf(fout, "%d %d\n", dp[1][n], sum - dp[1][n]);
	fclose(fout);
	fclose(fin);
	return 0;
}
