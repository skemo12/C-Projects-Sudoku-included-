#include <stdio.h>

int main () {

    int i,j,n,m,a[100][100];

    scanf("%d %d", &n, &m);
    i=0;
    while(i<n)
    {   
        if(i%2==0)
        for(j=0; j<m; j++)
            scanf("%d",&a[i][j]);
        else 
        for(j=m-1; j>=0; j--)
            scanf("%d",&a[i][j]);
        i++;
    }

        for (i=0; i<n; i++)
       {
            for(j=0; j<m; j++)
        {
            printf("%d ",a[i][j]);
        }
       
       }
        printf("\n");


    return 0;

}