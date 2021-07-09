#include <stdio.h>
#include <string.h>



int n,t,x,b[1000],k=1;
char s[1000];


int main () {

    scanf("%d %d\n",&n,&t);


    while (n>0) { 
        b[k]=n%2; 
        n=n/2; 
        k++; 
    } 
    

    for(int i=1;i<=t;i++){
        scanf("%s",s);
        if(s[0]=='S'){
            scanf("%d",&x);
            b[x]=1;

        }
        
        if(s[0]=='R'){
            scanf("%d",&x);
            b[x]=0;
        }

        if(s[0]=='P'){
             for(int j=k-1;j>=1;j--)
             printf("%d",b[j]);
             printf("\n");
        }
            


        
    }

    return 0;
}