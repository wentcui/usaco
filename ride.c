/*
ID: wentcui1
LANG: C
TASK: ride
*/
#include <stdio.h>
main () {
    FILE *fin  = fopen ("ride.in", "r");
    FILE *fout = fopen ("ride.out", "w");
    char c;
	int comet = 0, group = 0;
    fscanf (fin, "%c", &c);	/* the two input integers */
	while(!feof(fin)) {
		comet = c - 'A' + 1;
		fscanf(fin, "%c", &c);
		while (c != '\n') {
			comet = (comet % 47) * ((c - 'A' + 1) % 47);
			fscanf(fin, "%c", &c);
		}

		fscanf(fin, "%c", &c);
		group = c - 'A' + 1;
		fscanf(fin, "%c", &c);
		while (c != '\n' && !feof(fin)) {
			group = (group % 47) * ((c - 'A' + 1) % 47);
			fscanf(fin, "%c", &c);
		}

		if ((comet % 47) == (group % 47)) {
			fprintf(fout, "GO\n");
		} else {
			fprintf(fout, "STAY\n");
		}

		if (feof(fin))
			break;
		fscanf(fin, "%c", &c);
	}
    exit (0);
}
