#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long unsigned rec[35] = {0};
void pre(void) {
	rec[2] = 1;
	for(int i = 3; i <= 32; i++)
		rec[i] = 2 * rec[i - 1] + (1 << (i - 2));
}

int main() {
	int cases, caseno = 0;
	unsigned int N;
	long long unsigned ans = 0, cnt = 0;
	pre();
	scanf("%d", &cases);
	while(cases--) {
		scanf("%u", &N);
		ans = 0;
		cnt = 0;
		for(int i = 32; i > 0; i--) {
			if ((1 << (i - 1)) & N) {
				ans += rec[i - 1];
				ans += cnt * (1 << (i - 1));
				if (i < 32 && ((1 << i) & N))
					cnt += 1;
			}
		}
		ans += cnt;
		printf("Case %d: %llu\n", ++caseno, ans);
	}
	return 0;
}
