#include <stdio.h>

int main () { 

    int n,pozitie,element,vector[1000];

    scanf("%d\n",&n);
    for ( int i=0; i<n; i++)
        scanf("%d",&vector[i]);

    scanf("%d %d",&element,&pozitie);
    
    for (int i=n; i>pozitie; i--)
        vector[i]=vector[i-1];

    vector[pozitie]=element;
    n=n+1;

    for(int i=0; i<n; i++)
        printf("%d ",vector[i]);

    printf("\n");



    return 0;
}