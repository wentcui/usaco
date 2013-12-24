/*
ID: wentcui1
LANG: C++
TASK: fracdec
*/

#include<stdio.h>
#include<string.h>
FILE* fin=fopen("fracdec.in","r");
FILE* fout=fopen("fracdec.out","w");
bool mod[100010]={false};
int main()
{
    int n,d,decimal[100010],pos[100010],start,end,t;
    char result[100010];
    fscanf(fin,"%d%d",&n,&d);
    t=n/d;
    sprintf(result,"%d.",t);
    n-=d*t,start=-1,end=0,mod[n]=true,pos[n]=0;
    while(true)
    {
        n*=10;
        t=n/d;
        n-=d*t;
        decimal[end++]=t+'0';
        if(n==0)
        {
            break;
        }
        if(mod[n])
        {
            start=pos[n];
            break;
        }
        mod[n]=true;
        pos[n]=end;
    }
    int len=strlen(result);
    if(start==-1)
    {
        for(int i=0;i<end;i++)
        {
            result[len++]=decimal[i];
        }
        result[len]=0;
    }
    else
    {
        int i=0;
        while(i<start)
        {
            result[len++]=decimal[i++];
        }
        result[len++]='(';
        for(;i<end;i++)
        {
            result[len++]=decimal[i];
        }
        result[len++]=')';
        result[len]=0;
    }
    len=strlen(result);
    for(int i=0;i<len;i+=76)
    {
        fprintf(fout,"%.76s\n",result+i);
    }
    return 0;
}
