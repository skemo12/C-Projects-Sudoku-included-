#include <stdio.h>
#include <stdarg.h>
#include <string.h>


int calculus (const char *operatii,...)
{
    va_list args;
    va_start(args,operatii);
    int rez=0;
    int a;

    if (operatii[0]=='/' || operatii[0]=='%' || operatii[0]=='*')
    {
        rez=1;
    }
    for (int i = 0; i < strlen(operatii); i++)
    {
        switch (operatii[i])
        {
        case '+':
            a=va_arg(args,int);
            rez=rez+a;
            break;

        case '-':
            a=va_arg(args,int);
            rez=rez-a;
            break;
        
        case '%':
            a=va_arg(args,int);
            rez=rez%a;
            break;

        case '/':
            a=va_arg(args,int);
            rez=rez/a;
            break;
        case '*':
            a=va_arg(args,int);
            rez=rez*a;
            break;
        
        default:
            break;
        }

    }
    va_end(args);

    return rez;
    
}

int main () 
{
    printf("%d\n",calculus("++-*",1,1,1,2));

   return 0;
}