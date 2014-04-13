#include <stdio.h>
#include <string.h>

int main() {
	FILE *fin = fopen("q2.in", "r");
	FILE *fout = fopen("q2.out", "w");
	int cases, caseno = 0, tick = 0;
	double C, F, X, lastt, nextt;
	fscanf(fin, "%d", &cases);
	while(cases--) {
		fscanf(fin, "%lf %lf %lf", &C, &F, &X);
		lastt = (X / 2);
		tick = 0;
		while(1) {
			nextt = lastt - X / (2 + tick * F) + C / (2 + tick * F) + X / (2 + (tick + 1) * F);
			if (nextt > lastt)
				break;
			lastt = nextt;
			tick++;
		}
		fprintf(fout, "Case #%d: %.7lf\n", ++caseno, lastt);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
