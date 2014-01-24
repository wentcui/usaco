/*
ID: wentcui1
PROG: cowcycle
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string.h>
#define MAX 11
using namespace std;
ifstream fi("cowcycle.in");
ofstream fo("cowcycle.out");

void sc1(int, int);
void sc2(int, int);
void count();
void print();

int s1[MAX],s2[MAX],ans1[MAX],ans2[MAX];
int F,R,F1,F2,R1,R2,cnt;
double rate[MAX*MAX],diff[MAX*MAX],minvf=0x7FFFFFFF;
FILE* fin = fopen("cowcycle.in", "r");
FILE* fout = fopen("cowcycle.out", "w");

int main() {

	fscanf(fin, "%d%d%d%d%d%d", &F, &R, &F1, &F2, &R1, &R2);
	cnt = F * R;
	sc1(1, F1);
	print();
	return 0;
}

void sc1(int k, int w) {
	if (k == F + 1) {
		sc2(1, R1);
		return;
	}

	for(int i = w; i <= F2 - (F - k); i++) {
		s1[k] = i;
		sc1(k + 1, i + 1);
	}
}

void sc2(int k,int w)
{
	int i;
	if (k==R+1)
	{
		if (s1[F]*s2[R]<3*s1[1]*s2[1])
			return;
		count();
		return;
	}
	for (i=w;i<=(R2-(R-k));i++)
	{
		s2[k]=i;
		sc2(k+1,i+1);
	}
}

void count()
{
	int i,j,k=0,l;
	double sum=0,avg,vf=0,sumf=0,p;
	for (i=1;i<=F;i++)
		for (j=1;j<=R;j++)
		{
			p=(double)s1[i]/s2[j];
			l=++k;
			while (rate[l-1]>=p)
			{
				rate[l]=rate[l-1];
				l--;
			}
			rate[l]=p;
		}
	for (i=1;i<=cnt-1;i++)
	{
		diff[i]=rate[i+1]-rate[i];
		sum+=diff[i];
		sumf+=diff[i]*diff[i];
	}
	avg=sum/(cnt-1);
	vf=sumf-sum*avg;
	if (vf<minvf)
	{
		minvf=vf;
		memcpy(ans1+1,s1+1,sizeof(int)*F);
		memcpy(ans2+1,s2+1,sizeof(int)*R);
	}
}

void print()
{
	int i;
	for(i=1;i<=F-1;i++)
		fprintf(fout, "%d ", ans1[i]);
	fprintf(fout, "%d\n", ans1[i]);
	for(i=1;i<=R-1;i++)
		fprintf(fout, "%d ", ans2[i]);
	fprintf(fout, "%d\n", ans2[i]);
	fclose(fin);
	fclose(fout);
}
