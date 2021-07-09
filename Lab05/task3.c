#include <stdio.h>

int main () { 

    int n,permutari,vector[101],aux[101];

    scanf("%d",&n);
    for ( int i=0; i<n; i++)
        scanf("%d",&vector[i]);

    scanf("%d",&permutari);

    for(int i=0; i<permutari; i++)
        aux[i]=vector[i];

    for(int i=permutari; i<n; i++)
        vector[i-permutari]=vector[i];

    int k=0;
    for (int i=n-permutari; i < n; i++)
        vector[i]=aux[k++];

    for(int i=0; i<n; i++)
        printf("%d ",vector[i]);

    printf("\n");

    

    return 0;
}
