#include <stdio.h>

int main () {

    int n,v[100000],i,j,nr=0,a[100][100];
    int sus,jos,st,dr;

    scanf("%d",&n);
    for(i=0; i<n*n; i++)
        scanf("%d",&v[i]);


    sus=0;jos=n-1;
    st=0;dr=n-1;

    while(nr<n*n)
    {
        for(i=st;i<=dr;i++)
        {
        a[sus][i]=v[nr];
        nr=nr+1;
        }

        for(i=sus+1; i<=jos; i++)
        {
        a[i][dr]=v[nr];
        nr=nr+1;
        }

        for(i=dr-1;i>=st;i--)
        {
        a[jos][i]=v[nr];
        nr=nr+1;
        }

        for(i=jos-1;i>=sus+1;i--)
        {
        a[i][st]=v[nr];
        nr=nr+1;
        }

        st=st+1;
        dr=dr-1;
        sus=sus+1;
        jos=jos-1;
        
    }

    for (i=0; i<n; i++)
       {
            for(j=0; j<n; j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
       }


    return 0;

}