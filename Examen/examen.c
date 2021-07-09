#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enumerativ ( int x )
{
    int ok = 1;
    int cx = x;
    int n = 0;

    while (cx>0)
    {
        n++;
        cx=cx/10;
    }

    int *v = (int *) calloc(n,sizeof(int));
    int *aux = (int *) calloc(n,sizeof(int));
    cx=x;
    int i = 0;
    while (cx>0)
    {
        aux[i++] = cx%10;
        cx=cx/10;
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = aux [n-i-1];
    }
    
    i=0;
    int met = 1;

    while (i < n)
    {
        int a = 0, b = 0;
        int len1 = 0, len2 = 0;
        for (int j = 0; j < met; j++)
        {
            a = v[i+j] + a*10;
            len1++;
        }
        for (int j = 0; j < met; j++)
        {
            b = v[i+j+len1] + b*10;
            len2++;
        }
        if(a!=(b-1))
        {
            b = b*10+v[i+len2+1];
            len2++;
        }
        if(a!=(b-1))
        {
            met++;
            i = 0;
        }
        else 
        {
            i = i + len1 + len2;
            
        }
        if (met > n)
        {
            
            ok = 0;
            i = n;
        }
    }
    free(aux);
    free(v);
    return ok;
}

int enumerativ2 (int *v, int n)
{
    int ok = 1; 
    int i=0;
    int met = 1;

    while (i < n)
    {
        int a = 0, b = 0;
        int len1 = 0, len2 = 0;
        for (int j = 0; j < met; j++)
        {
            a = v[i+j] + a*10;
            len1++;
        }
        for (int j = 0; j < met; j++)
        {
            b = v[i+j+len1] + b*10;
            len2++;
        }
        if(a!=(b-1))
        {
            b = b*10+v[i+len2+1];
            len2++;
        }
        if(a!=(b-1))
        {
            met++;
            i = 0;
        }
        else 
        {
            i = i + len1 + len2;
            
        }
        if (met > n)
        {
            
            ok = 0;
            i = n;
        }
    }
    return ok;
}

int main () 
{   
    int a[] = {1,0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,1,8,1,9};
    int ok = enumerativ2(a,20);

    return 0;
}