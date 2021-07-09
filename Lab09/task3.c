#include <stdio.h>
#include <stdlib.h>

int main () {

    int n;
    scanf("%d",&n);

    int ***cub = (int***)calloc(n,sizeof(int**));
    for ( int i = 0; i < n*n; i++)
    {
        cub[i]= (int**)calloc(n,sizeof(int*));
        for ( int j = 0; j < n; j++)
            cub[i][j]= (int*)calloc(n,sizeof(int));
    }

    for ( int i = 0; i<n; i++ )
    {
        for ( int j = 0; j<n; j++ )
        {
            for ( int k = 0; k<n; k++ )
            {
                scanf("%d",&cub[i][j][k]);
            }
        }

    }



    for ( int i = 0; i<n; i++ )
    {
        for ( int j = 0; j<n; j++ )
            printf("%d ",cub[n-1-i][0][j]);
         
        printf("\n");
    }
    printf("\n");


     for ( int i = 0; i<n; i++ )
    {
        for ( int j = 0; j<n; j++ )
            printf("%d ",cub[0][i][j]);
        
         printf("\n");
    }
    printf("\n");

     for ( int i = 0; i<n; i++ )
    {
        for ( int j = 0; j<n; j++ )
            printf("%d ",cub[i][n-1][j]);

         printf("\n");
    }
    printf("\n");

       for ( int i = 0; i<n; i++ )
    {
        for ( int j = 0; j<n; j++ )
            printf("%d ",cub[n-1][n-1-i][j]);

         printf("\n");
    }



    free(cub);


    return 0;
}