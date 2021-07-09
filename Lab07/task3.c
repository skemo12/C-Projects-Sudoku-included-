#include <stdio.h> 
#include <string.h>

int makeDouble (int x)
{
    return 2*x;
}

int makeTriple (int x)
{
    return 3*x;
}

int makeHalf (int x)
{
    return x/2;
}

void map(int (*f)(int),int *v,int n)
{
    for(int i=0;i<n;i++)
    {
    *v=(*f)(*v);
    v++;
    }
}



int main () { 
    int n, v[1001], *p;
    int* f(int);
    char name[100];

    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&v[i]);
    
    scanf("%s",name);
    p=&v[0];
    switch (name[4]) {
        case 'D': 
            map(makeDouble,p,n);
            break;
        case 'T': 
            map(makeTriple,p,n);
            break;
        case 'H': 
            map(makeHalf,p,n);
            break;

    }
   
    for(int i=0;i<n;i++)
        printf("%d ",v[i]);

    printf("\n");


    return 0;
}
