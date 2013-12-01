/*
ID: wentcui1
LANG: C++
TASK: ariprog
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

struct Node{
	int a;
	int b;
};

template<class T>
struct cmp
{
public:
	bool operator()(const T& x, const T& y) const
	{
		if(x.b != y.b)
			return x.b < y.b;
		return x.a < y.a;
	}
};

struct Node res[10000];

int main ()
{
	ofstream output;
	ifstream input;
	int N, M, pos = 0;
	bool *map, NONE = true;
	input.open ("ariprog.in");
	input >> N;
	input >> M;
	output.open("ariprog.out");
	
	map = new bool[2 * M * M + 1];
	memset(map, false, 2 * M * M + 1);
	for(int i = 0; i <= M; i++) {
		for(int j = 0; j <= M; j++) {
			map[i * i + j * j] = true;
		}
	}

	for(int diff = 1; diff <= M * M; diff++) {
		pos = 0;
		for(int start = 0; start <= diff; start++) {
			if (start + (N - 1) * diff > 2 * M * M)
				break;
			int runningstart = start, len = 0, runningnum = start;
			while(runningnum <= 2 * M * M) {
				if (map[runningnum]) {
					len++;
					if (len == 1) {
						runningstart = runningnum;
					}
				}
				
				if (!map[runningnum] || runningnum + diff > 2 * M * M){
					if (len >= N) {
						for(int outputnum = 0; outputnum <= len - N; outputnum++) {
							res[pos].a = runningstart + outputnum * diff;
							res[pos].b = diff;
							pos++;
						}
					}
					if (runningnum + N * diff > 2 * M * M)
						break;
					len = 0;
				}
				runningnum += diff;
			}
		}
		if (pos > 0) {
			sort(res, res + pos, cmp<Node>());
			for(int i = 0; i < pos; i++) {
				output << res[i].a << " " << res[i].b << "\n";
			}
			NONE = false;
		}
	}
	if (NONE)
		output << "NONE" << endl;
	output.close();
	return 0;
}
