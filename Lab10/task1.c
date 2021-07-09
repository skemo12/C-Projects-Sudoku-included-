#include <stdio.h>


typedef struct  
{
    int real,imaginar;
} numereComplexe;

int main () {

    numereComplexe v[1001],aux;

    int n;

    scanf("%d\n",&n);

    for (int i=0; i<n; i++)
    {
        scanf("(%d, %d)\n",&v[i].real,&v[i].imaginar);
    }

    for (int i=0; i<n-1; i++)
    {
        int modul;
        modul=(v[i].real*v[i].real)+(v[i].imaginar*v[i].imaginar);

        for (int j=i+1; j<n; j++)
        {
            int modul2;
            modul2=(v[j].real*v[j].real)+(v[j].imaginar*v[j].imaginar);
            
            if (modul2<modul)
            {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }

            if (modul2==modul)
            {
               if (v[i].real>v[j].real)
               {
                    aux=v[i];
                    v[i]=v[j];
                    v[j]=aux;
               }

               if (v[i].real==v[j].real)
               {
                   if (v[i].imaginar>v[j].imaginar)
                   {
                        aux=v[i];
                        v[i]=v[j];
                        v[j]=aux;
                   }
               }
            }

        }
    }

    for (int i=0; i<n; i++)
    {
        printf("(%d, %d)\n",v[i].real,v[i].imaginar);
    }


return 0;
}