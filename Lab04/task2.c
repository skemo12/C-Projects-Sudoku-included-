#include <stdio.h>

long n,k1,k2;

long modificare_aparitie( long n , long k1 , long k2 ){ 

    long p=1,cn;
    cn=n;
    while ( cn != 0 ) { 

        if(cn%10==k1) n=(n/p/10*10 + k2)*p+n%p;

        cn=cn/10;
        p=p*10;

    }

    return n;
    
}

int main () { 

    scanf("%ld %ld %ld",&n,&k1,&k2);
    n=modificare_aparitie(n,k1,k2);
    printf( "%ld\n",n);
    
    return 0;

}