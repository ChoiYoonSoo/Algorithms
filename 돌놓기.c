#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int i, j;
	int t, n;
	int dp[3][100000];

	scanf("%d", &n);

	for (i = 0; i < 3; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &dp[i][j]);

	dp[0][1] += dp[1][0];
	dp[1][1] += dp[0][0];

	for (i = 2; i < n; i++) {
		dp[0][i] += (dp[1][i - 1] > dp[1][i - 2] ? dp[1][i - 1] : dp[1][i - 2]);

		dp[1][i] += (dp[0][i - 2] > dp[0][i - 1] ? dp[0][i - 2] : dp[0][i - 1]);
	}

	printf("%d\n", dp[0][n - 1] > dp[1][n - 1] ? dp[0][n - 1] : dp[1][n - 1]);

	return 0;
}