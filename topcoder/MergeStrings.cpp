#ifndef debuging
#define FIN  ;
#define FOUT ;
#define OUT(x)  ;
#define ERR(x)  ;
#endif
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std ;
#define For(i , n) for(int i = 0 ; i < (n) ; ++i)
#define SZ(x)  (int)((x).size())
typedef long long lint ;
const int maxint = -1u>>2 ;
const double eps = 1e-6 ;


class MergeStrings
{
	public:
		void reverse (string &str) {
			int s = 0, e = str.size() - 1;
			while(s < e) {
				char c = str[s];
				str[s] = str[e];
				str[e] = c;
				s++, e--;
			}
		}

		int choose(int i, string A, int j, string B) {
			while(i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
				i--, j--;
			}
			if (i > 0 && j > 0) {
				if (A[i - 1] > B[j - 1])
					return 2;
				return 1;
			}
			if (i > 0)
				return 1;
			return 2;
		}

		string getmin(string S, string A, string B) {
			string ret;
			int i, j, k, ni, nj, ri;
			bool dp[51][51][51] = {{{false}}};
			char min_c = 'Z' + 1;
			reverse(S);
			reverse(A);
			reverse(B);
			for(i = 1; i <= A.size(); i++) {
				if (S[i - 1] == '?' || S[i - 1] == A[i - 1])
					dp[i][0][i] = true;
				else
					break;
			}
			for(i = 1; i <= B.size(); i++) {
				if (S[i - 1] == '?' || S[i - 1] == B[i - 1])
					dp[0][i][i] = true;
				else
					break;
			}
			dp[0][0][0] = true;
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
				}
			if (!dp[A.size()][B.size()][S.size()])
				return "";
			k = S.size();
			i = A.size();
			j = B.size();
			ni = nj = 0;
			while(k > 0) {
				min_c = 'Z';
				//cout << i << " " << j << endl;
				if (A[i - 1] == B[j - 1] && dp[i - 1][j][k - 1] && dp[i][j - 1][k - 1]) {
					//printf("start choose\n");
					ri = choose(i, A, j, B);
					//printf("ri: %d\n", ri);
					if (ri == 1) {
						ret += A[i - 1];
						i--;
					} else {
						ret += B[j - 1];
						j--;
					}
					k--;
					continue;
				}
				if (i >= 1 && (S[k - 1] == '?' || S[k - 1] == A[i - 1]) && dp[i - 1][j][k - 1]) {
					if (A[i - 1] <= min_c) {
						min_c = A[i - 1];
						ni = i - 1;
						nj = j;
					}
				}
				if (j >= 1 && (S[k - 1] == '?' || S[k - 1] == B[j - 1]) && dp[i][j - 1][k - 1]) {
					if (B[j - 1] <= min_c) {
						min_c = B[j - 1];
						ni = i;
						nj = j - 1;
					}
				}
				ret += min_c;
				i = ni, j = nj;
				k--;
			}
			return ret;
		}




};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
