#include <stdio.h>

int main () {   
    int n,pozitie,vector[101];
    
    scanf("%d\n",&n);
    for ( int i=0; i<n; i++)
        scanf("%d",&vector[i]);

    scanf("%d",&pozitie);

    for ( int i=pozitie; i<n-1; i++)   
        vector[i]=vector[i+1];
    
    n=n-1;

    for(int i=0; i<n; i++)
        printf("%d ",vector[i]);
    
    printf("\n");
             
    
    return 0;
}