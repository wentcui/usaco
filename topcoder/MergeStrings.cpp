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
		string getmin(string S, string A, string B) {
			string dp[51][51];
			string str;

			for(int i = 1; i <= A.size(); i++) {
				if (A[i - 1] == S[i - 1] || S[i - 1] == '?')
					dp[i][0] = dp[i - 1][0] + A[i - 1];
				else
					break;
			}
			for(int i = 1; i <= B.size(); i++) {
				if (B[i - 1] == S[i - 1] || S[i - 1] == '?')
					dp[0][i] = dp[0][i - 1] + B[i - 1];
				else
					break;
			}

			for(int i = 1; i <= A.size(); i++) {
				for(int j = 1; j <= B.size(); j++) {
					int k = i + j;
					str = "[";
					if (dp[i - 1][j].size() > 0 && (S[k - 1] == '?' || S[k - 1] == A[i - 1]))
						str = min(str, dp[i - 1][j] + A[i - 1]);
					if (dp[i][j - 1].size() > 0 && (S[k - 1] == '?' || S[k - 1] == B[j - 1]))
						str = min(str, dp[i][j - 1] + B[j - 1]);
					dp[i][j] = str;
				}
			}
			return dp[A.size()][B.size()];
		}




};

int main(){
	MergeStrings mg;
	cout << mg.getmin("???????????", "AZZAA", "AZAZZA");
	return 0;
}


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
