/*
ID: wentcui1
LANG: C
TASK: friday
*/
#include <stdio.h>
void caculate(int days, int *mon, int *tue, int *wed, int *thu, int *fri, int *sat, int *sun) {
	int d = days + 13;
	switch(d % 7) {
		case 0: (*sun) += 1; break;
		case 1: (*mon) += 1; break;
		case 2: (*tue) += 1; break;
		case 3: (*wed) += 1; break;
		case 4: (*thu) += 1; break;
		case 5: (*fri) += 1; break;
		case 6: (*sat) += 1; break;
	}
}
main () {
    FILE *fin  = fopen ("friday.in", "r");
    FILE *fout = fopen ("friday.out", "w");
    int n, i, days = 0;
	int mon, tue, wed, thu, fri, sat, sun;
	mon = tue = wed = thu = fri = sat = sun = 0;
    fscanf (fin, "%d", &n);
	for(i = 0; i < n; i++) {
		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;
		
		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		if (((1900 + i) % 100 != 0 && (1900 + i) % 4 == 0) || (1900 + i) % 400 == 0)
			days += 29;
		else
			days += 28;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 30;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 30;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 30;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 30;

		caculate(days, &mon, &tue, &wed, &thu, &fri, &sat, &sun);
		days += 31;
	}

	fprintf(fout, "%d ", sat);
	fprintf(fout, "%d ", sun);
	fprintf(fout, "%d ", mon);
	fprintf(fout, "%d ", tue);
	fprintf(fout, "%d ", wed);
	fprintf(fout, "%d ", thu);
	fprintf(fout, "%d\n", fri);

	exit(0);
}
