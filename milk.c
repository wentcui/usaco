/*
ID: wentcui1
LANG: C
TASK: milk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
	int price;	
	int quant;
};

int
milkcmp(const void *va, const void *vb)
{
    struct node *a, *b;

    a = (struct node*)va;
    b = (struct node*)vb;

    if(a->price > b->price)
		return 1;
    if(a->price < b->price)
		return -1;
    return 0;
}

main()
{
	FILE *fin = fopen("milk.in", "r");
    FILE *fout = fopen("milk.out", "w");
	struct node *nodearr;
	int total, num, i, ret = 0;
	fscanf(fin, "%d %d", &total, &num);
	fgetc(fin);
	nodearr = (struct node *)malloc(sizeof(struct node) * num);
	memset(nodearr, 0, sizeof(struct node) * num);

	for(i = 0; i < num; i++) {
		fscanf(fin, "%d %d", &nodearr[i].price, &nodearr[i].quant);
	}
	qsort(nodearr, num, sizeof(struct node), milkcmp);
	
	for(i = 0; i < num; i++) {
		if (total > nodearr[i].quant) {
			ret += (nodearr[i].quant * nodearr[i].price);
			total -= nodearr[i].quant;
		} else {
			ret += (nodearr[i].price * total);
			break;
		}
	}
	fprintf(fout, "%d\n", ret);
	exit(0);
}
