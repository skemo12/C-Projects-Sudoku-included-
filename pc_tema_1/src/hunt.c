#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;
    uint64_t mask = 1<<5;
    mask=mask-1; // mask == 5 biti de 1
    

    /* TODO */

    int ok=1;

    while(ok)
    {
        if ( (memory & mask) == mask ) ok=0; 
            memory=memory>>1;
    }

    memory=memory>>4;
    mask=1<<16;
    mask=mask-1; //16 de 1 pentru a obtine cei 16 biti pentru spell
    res=memory&mask; 
    

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    /* TODO */

    int ok=1,i=0;
    uint64_t cpmem,mask;

    cpmem=memory;
    mask=1<<3;
    mask=mask-1;// 7=3 biti de 1

    while(ok)
    {
        if ( (memory & mask) == mask ) ok=0; 
        memory=memory>>1;
        i++;
    }

    i=i-17;
    cpmem=cpmem>>i;
    mask=1<<16;
    mask=mask-1;  //16 de 1 pentru a obtine cei 16 biti pentru spell
    res=cpmem&mask;
                    

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)

{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    /* TODO */

    //Daca spell_encrypted = spell_plaintext ^ key,atunci
    //spell_plaintext= spell_encrypted ^ key.
    //Mai exact, inversa functiei XOR este tot XOR.

    res=spell^key;

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */

    unsigned int count=0;
    uint32_t sword=0;
    uint16_t value=0;

    for(int i=0;i<16;i++)
    {
        if( (enemy>>i) & 1 ) count++;
    }

    if(count%2==0) 
    {
        sword=sword|(1<<31);
        sword=sword|(1<<28);
        value=( enemy & (1-enemy) )^0;       

    }
    else 
    {
        sword=sword|(1<<30);
        sword=sword|(1<<29);
        value=-enemy;
    }

    sword=sword|value;
    res=sword;

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    /* TODO */
    uint16_t antibodies_high=0;

    /* if bit i of cocktail is 0 ,then both bits i in 
    antibodies_high and antibodies_low need to be 0.
    if bit i of cocktail is 1, then the i bit in
    antibodies_high needs to be 1, so the i bit in
    antibodies_low needs to be 0*/
    
    // So antibodies_low is always 0


    for (int i=0; i<32; i++)
        if( (cocktail >> i) & 1 ) 
            antibodies_high=antibodies_high|(1ULL<<i);   
       

    res=antibodies_high<<16;
    
    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;
    
    /* TODO */

    uint8_t mask;
    int ok0_1=1,ok0_2=1,ok1=1,ok2=1;

    mask=1<<4;
    mask=mask-1;  //4 biti de 1

    
    //verificare Wolven Glade
    for( int i=0; i<64;i++)
        if( ( (map>>i) & 1 ) != 1 ) 
            ok2=0;

    //verificare Brokilon ( varianta fara copaci)
    for( int i=0; i<64;i++)
        if(((map>>i)&1)!=0) 
            ok0_1=0;
    
    //verificare Hindar
    for( int i=0; i<64;i++)
        if( i!=31 && i!=32 ) 
        {
            if ( ( (map>>i)&1 )== 1 ) 
                ok1=0;
        }
        else {
            uint8_t bit1,bit2;

            bit1=(map>>31)&1ULL;
            bit2=(map>>32)&1ULL;

            if ( bit1!=1 && bit2!=1 ) 
                ok1=0;
            }

    //verificare Brokilon ( perechi de 4 copaci )
    int i=0;

    while(i<64)
    {
        uint8_t shift;
        shift=(map>>i);
        if( (shift & 1) == 1 ) 
        {
            if ( (shift& mask) != mask ) 
                ok0_2=0;
            i=i+3;
        }

        i=i+1;
    }
    
    //consideram padurea defaulta padurea Caed, fiind cea care nu are o regula anume.
    res=3;
    if( ok0_1 || ok0_2 ) res=0;
    if( ok1 ) res=1;
    if( ok2 ) res=2;

    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */

    int poz1=-1, poz2=0;

    for(int i=0;i<32;i++)
        if ( ( (map>>i)&1) == 1 )
        { 
            if (poz1==-1) poz1=i;
            else poz2=i;
        }
        
    res=poz2-poz1;

    return res;
}
