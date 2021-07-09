#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

int main (){

    int n,cifra,p,len=0;
    char s[100],o[200],c;
    char buffer[50];

    fgets(s,100,stdin);
    scanf("%c",&c);

    n=1;
    p=10;


    for ( int i=0; i<=strlen(s); i++)
    {
       
        if (s[i]==c)
        {
            sprintf(buffer,"%d",n);
            for( int j=0; j<strlen(buffer); j++){
                o[len++]=buffer[j];
                
            }
            n++;
            
        }
        else { 
            o[len]=s[i];
            len++;
        }
    }
    o[len]='\0';
    printf("%s",o);

    return 0;

}