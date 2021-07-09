#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    res=(nr>>i) & 1ULL;

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

	res= nr^(1ULL<<i);
      
	
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    res=nr|(1ULL<<i);

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    res=nr&~(1ULL<<i);

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    res=nand_gate(a,b);
    res=nand_gate(res,res);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res=nand_gate(a,a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    res=nand_gate(nand_gate(a,a) , nand_gate(b,b)); 

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    uint8_t temp = -1;
    temp=nand_gate(a,b);
    res=nand_gate(nand_gate(temp,a),nand_gate(b,temp));

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    uint8_t sumhalf,carryhalf,sum,carry,aux;
    
    res=0;
   
    sumhalf=xor_gate(a,b);
    carryhalf=and_gate(a,b);
    aux=and_gate(sumhalf,c);
    sum=xor_gate(sumhalf,c);
    carry=or_gate(carryhalf,aux);

    if (sum) res=activate_bit(res,1);
    if (carry) res=activate_bit(res,0);


    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */
    uint8_t sum=0, carry_in=0,carry_out,bit1,bit2,res1;
    uint64_t sumaf=0; 

    res=0;


    for ( uint8_t i=0 ; i<64 ; i++ ){

        bit1=get_bit(a,i);
        bit2=get_bit(b,i);
        res1=full_adder(bit1,bit2,carry_in);
        sum=get_bit(res1,1);
        carry_out=get_bit(res1,0);

       
        if (sum) sumaf=activate_bit(sumaf,i);
    
        carry_in=carry_out;
    }


    if( carry_in>0 ) res=0;
    else  res=sumaf;


    return res;
}
