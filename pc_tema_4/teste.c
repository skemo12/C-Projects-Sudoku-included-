#include "utils.h"

typedef struct struct0
{
	char zero;

} struct0;

typedef struct struct1 
{
	char a,b;

} struct1;

typedef struct struct2 
{
	int a;
	struct1 *doi;
} struct2;



int main () 
{

	char ab[100];

	int x,y;

	struct2 *abc;
	abc = (struct2 *) calloc(10,sizeof(struct2));
	abc->doi=(struct1 *) calloc(10,sizeof(struct1));
	abc->doi[1].a = 'a';
	printf("%c\n",abc->doi[1].a);

	free(abc->doi);

	struct1 *ad = (struct1 *) calloc(10,sizeof(struct1));


	//struct2->doi[1]->a = 'a';



    return 0;
}