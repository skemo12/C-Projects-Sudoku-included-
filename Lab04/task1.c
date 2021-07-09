#include <stdio.h>

long n,on;

long oglindit ( long n , long p) {

    if ( n==0 ) return p;
    else return oglindit(n/10,p*10+n%10);


}
//n=1234 oglindit ( 123,4 )
// n=123 oglindit ( 12,43)

// n=1 oglindit (0,4321)
// n=0  
int main () { 

    scanf("%ld",&n);
    on=oglindit(n,0);
    printf( "%ld\n",on);
    
    return 0;
    
    
}