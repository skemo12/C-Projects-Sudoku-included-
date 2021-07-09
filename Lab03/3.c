#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


uint8_t nr,i,res,mask;

int main () {


    nr=1;
    i=1;
    res=(nr<<1)|i;
    

    printf( "%hu\n" ,res);

return 0;
}
/*
 uint64_t sum, carry=0,bit1,bit2 ;

    for ( int i=0 ; i<64 ; i++ ){

        bit1=get_bit(a,i);
        bit2=get_bit(b,i);
        sum=get_bit( full_adder(bit1,bit2,carry) , 1 ); 
        carry=get_bit (full_adder(bit1,bit2,carry) , 0 );

        if (carry) res=or_gate( or_gate( carry<<(i+1) ,sum<<i), res);
        else res=or_gate(res, sum<<i);




    }
    */ 
