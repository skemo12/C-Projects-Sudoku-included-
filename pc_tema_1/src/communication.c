#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    uint8_t character[10]={18,9,3,11};

    for(int i=0; i<4; i++)
        send_squanch(character[i]);


}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t message;
    char c, alfabet[30];

    c='A';
    
    for(int i=1 ; i<27; i++)
    {
         alfabet[i]=c;
         c++;
    }
   
    for(int i=0 ; i<5; i++)
    {
        message=recv_squanch();

        for (int j=1; j<27; j++)
            if(message==j) c=alfabet[j];


        fprintf(stdout,"%c",c);
    }

}
    



void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    uint8_t message;
    
    for(int i=1; i<=10; i++)
    {
        message=recv_squanch();
        send_squanch(message);
        send_squanch(message);
    }

}

/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */

    uint64_t len, message[15]={8, 5, 12, 12, 15, 20, 8, 5, 18, 5};
    // elementele vectorului message sunt litere mesajului HELLOTHERE.

    
    len=10;
    len=len<<2;
    send_squanch(len);

    for(int i=0; i<=9;i++)
        send_squanch(message[i]);

}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t len, message;
    char c,alfabet[30];
     c='A';
    
    for(int i=1 ; i<27; i++)
    {
         alfabet[i]=c;
         c++;
    }

    len=recv_squanch();
    len=len<<2;
    len=len>>4;

    fprintf(stdout,"%d",len);

    for(int i=1; i<=len; i++)
    {
        message=recv_squanch();
            for ( int j=1; j<27; j++ )
            if(message==j) c=alfabet[j];
  

         fprintf(stdout,"%c",c);

    }

}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    uint8_t len, message,len_p,len_v;
    uint8_t pickle[]= {16, 9, 3, 11, 12, 5, 18, 9, 3, 11};
    uint8_t vindi[]= {22, 9, 14, 4, 9, 3, 1, 20, 15, 18, 19};

    len=recv_squanch();
    len=len<<2;
    len=len>>4;

    len_p=40;
    len_v=44;


    for(int i=1; i<=len; i++)
        message=recv_squanch();
    

    if(message==16)
    {
        send_squanch(len_p);
        for(int j=0; j<10; j++) 
            send_squanch(pickle[j]);
    }
    else 
    {
        send_squanch(len_v);
        for(int j=0; j<11; j++) 
            send_squanch(vindi[j]);    
    }

}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t res=0;

    for (int i=0 ; i<4; i++)
    {
        uint8_t aux=0;

        aux=(c2>>i)&1;
        aux=aux<<(2*i);
        res=res|aux;

        aux=(c1>>i)&1;
        aux=aux<<(2*i+1);
        res=res|aux;
    }   

    send_squanch(res);

}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */

    res = 0;

    for (int i=0; i<=4; i++)
    {
        uint8_t aux=0;

        aux=(c>>2*i)&1;
        aux=aux<<i;
        res=res|aux;

        aux=(c>>(2*i+1))&1;
        aux=aux<<(i+4);
        res=res|aux;
    }

    return res;
}
