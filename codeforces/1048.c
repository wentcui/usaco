#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, k, rec[1024];

int judge(int key) {
	int i, j, s, num = 0;
	for(i = 1; i <= n + 1;) {
		if (rec[i] > key)
			return 0;
		s = rec[i++];
		for(; i <= n + 1; i++) {
			if (s + rec[i] <= key) {
				s += rec[i];
				num++;
			} else
				break;
		}
	}
	
	if (num >= n - k)
		return 1;
	return 0;
}

void print(int key) {
	int sum = 0, i, j;
	int ln = k + 1, lc = n + 1;
	for(i = 1; i <= n + 1;) {
		sum = rec[i++];
		ln--, lc--;
		while(sum + rec[i] <= key && lc > ln) {
			sum += rec[i];
			lc--;
			i++;
		}
		printf("%d\n", sum);
	}
}

int fn(int sum) {
	int l = 0, r = sum, mid;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (judge(mid))
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main() {
    int cases, caseno = 0;
    int i, j, sum, key;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d %d", &n, &k);
        for(i = 1, sum = 0; i <= n + 1; i++) {
            scanf("%d", &rec[i]);
			sum += rec[i];
        }
		key = fn(sum);
        printf("Case %d: %d\n", ++caseno, key);
		print(key);
    }
    return 0;
}

