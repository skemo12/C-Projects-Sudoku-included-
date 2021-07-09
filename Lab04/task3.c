#include <stdio.h>

long n;

long concatenare (long n){ 

    long parteadr,parteast,l1,l2,p;
    parteadr=0; parteast=0;
    l1=l2=1;

    while ( n!=0 ) {

        if( n%2==1 ){ 
            parteadr=parteadr+l2*(n%10);
            l2=l2*10;
        }
        else {
            parteast=parteast+l1*(n%10);
            l1=l1*10;
        }

        n=n/10;

    }

    n=parteast*l2+parteadr;

    return n;
}

int main () {

    scanf("%ld",&n);
    n=concatenare(n);
    printf( "%ld\n",n);

    return 0;

}