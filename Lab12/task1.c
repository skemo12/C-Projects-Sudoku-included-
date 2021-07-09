#include <stdio.h>
#include <stdarg.h>

#define MAX(a,b) { \
    if (b>a) \
    { \
        a=b; \
    } \
} 

int max (int a,...)
{
    va_list args;
    va_start(args,a);
    int b;
    b=va_arg(args,int);
    while (b>=0)
    {
        MAX(a,b);
        b=va_arg(args,int);
    }

    return a;

}

int main () {


    printf("%d\n",max(5,16,7,8,-1));

    return 0;
}