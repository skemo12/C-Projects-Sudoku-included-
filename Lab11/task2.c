#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *openFile(char *filename, char *acccesMode)
{
    FILE *file = fopen(filename, acccesMode);
    if (!file)
    {
        exit (1);
    }
}

int sizeofFile (FILE *file)
{
    fseek(file,0,SEEK_END);
    int count= ftell(file);
    fseek(file,0,SEEK_SET);
    return count;
}

int main () {

    char cuv1[50], cuv2[50];
    
    FILE *fisier=openFile("text.in","rt");
    
    int marime = sizeofFile(fisier);
    
    char *prop=(char*)calloc(marime,sizeof(char));
    char *res=(char*)calloc(marime,sizeof(char));

    fgets(cuv1,50,fisier);
    fgets(cuv2,50,fisier);
    fgets(prop,marime,fisier);
    
    printf("%d %s\n",marime,prop);
    
    int i = 0; 
    while (*prop) { 
        if (strstr(prop, cuv1) == prop) { 
            strcpy(&res[i], cuv2); 
            i=i+ strlen(cuv2); 
            prop=prop+ strlen(cuv1); 
        } 
        else
            res[i++] = *prop++; 

    } 

    printf("%s \n",res);

    



    return 0;
}