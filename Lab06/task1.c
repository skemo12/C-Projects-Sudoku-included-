#include <stdio.h>

int main () {
    
    int n,m,i,j,c,a[100][100],max;
    
    scanf("%d %d %d", &n, &m, &c);
    for (i=0; i<n; i++)
        for(j=0; j<m; j++)
            scanf("%d",&a[i][j]);
    
    for (i=0; i<n; i++)
    {   
        max=a[i][0];
        for(j=1; j<m; j++)
            if(max<a[i][j]) 
                max=a[i][j];
        a[i][c]=max;
    }

       for (i=0; i<n; i++)
       {
        for(j=0; j<m; j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
       }

    return 0;
}