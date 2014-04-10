#include <string>
#include <iostream>
using namespace std;

void reverse (string &str) {
	int s = 0, e = str.size() - 1;
	while(s < e) {
		char c = str[s];
		str[s] = str[e];
		str[e] = c;
		s++, e--;
	}
}

string getmin(string S, string A, string B) {
	string ret;
	int i, j, k, ni, nj;
	bool dp[51][51][51] = {{{false}}};
	char min_c = 'Z' + 1;
	reverse(S);
	reverse(A);
	reverse(B);
	cout << S << A << B << endl;
	dp[0][0][0] = true;
	printf("start\n");
	for(i = 1; i <= A.size(); i++)
		for(j = 1; j <= B.size(); j++) {
			k = i + j;
			if (S[k - 1] == '?')
				dp[i][j][k] = dp[i][j - 1][k - 1] | dp[i - 1][j][k - 1];
			else {
				if (S[k - 1] == A[i - 1])
					dp[i][j][k] = dp[i - 1][j][k - 1];
				if (S[k - 1] == B[j - 1])
					dp[i][j][k] |= dp[i][j - 1][k - 1];
			}
			cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
		}
	printf("end\n");
	if (!dp[A.size()][B.size()][S.size()])
		return "ffff";
	k = S.size();
	i = A.size();
	j = B.size();
	ni = nj = 0;
	while(k > 0) {
		min_c = 'Z' + 1;
		if (S[k - 1] == '?') {
			if (dp[i - 1][j][k - 1]) {
				if (A[i - 1] < min_c) {
					min_c = A[i - 1];
					ni = i - 1;
					nj = j;
				}
			} else {
				if (B[i - 1] < min_c) {
					min_c = B[i - 1];
					ni = i;
					nj = j - 1;
				}
			}
		} else {
			if (S[k - 1] == A[i - 1] && dp[i - 1][j][k - 1]) {
				if (A[i - 1] < min_c) {
					min_c = A[i - 1];
					ni = i - 1;
					nj = j;
				}
			}
			if (S[k - 1] == B[i - 1] && dp[i][j - 1][k - 1]) {
				if (B[i - 1] < min_c) {
					min_c = B[i - 1];
					ni = i;
					nj = j - 1;
				}

			}
		}
		ret += min_c;
		i = ni, j = nj;
		k--;
	}
	return ret;
}

int main() {
	string str = getmin("??CC??", "ABC", "BCC");
	cout << str << endl;
}
