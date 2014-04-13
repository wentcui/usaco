#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
	FILE *fin = fopen("q1.in", "r");
	FILE *fout = fopen("q1.out", "w");
	int cases, caseno = 0, a1, a2, v, count, ret;
	bool map[17] = {false};
	fscanf(fin, "%d", &cases);
	while(cases--) {
		memset(map, false, sizeof(bool) * 17);
		count = 0;
		fscanf(fin, "%d", &a1);
		for(int i = 1; i <= 4; i++) {
			for(int j = 1; j <= 4; j++) {
				fscanf(fin, "%d", &v);
				if (i != a1)	continue;
				map[v] = true;
			}
		}
		fscanf(fin, "%d", &a2);
		for(int i = 1; i <= 4; i++) {
			for(int j = 1; j <= 4; j++) {
				fscanf(fin, "%d", &v);
				if (i != a2)	continue;
				if(map[v]) {
					count++;
					ret = v;
				}
			}
		}
		fprintf(fout, "Case #%d: ", ++caseno);
		if (count == 0)
			fprintf(fout, "Volunteer cheated!\n");
		else if (count > 1)
			fprintf(fout, "Bad magician!\n");
		else
			fprintf(fout, "%d\n", ret);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
