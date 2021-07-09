#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "util/print_board.h"
#include "util/scrabble.h"

void adaugarePunctaj (char cuvant[25], int *player )
{
    //pentru fiecare indice, matricea retine literele ce valoareaza i puncte

    char punctaj[15][15];
    
    strcpy(punctaj[1],"AEILNORSTU");
    strcpy(punctaj[2],"DG");
    strcpy(punctaj[3],"BCMP");
    strcpy(punctaj[4],"FHVWY");
    strcpy(punctaj[5],"K");
    strcpy(punctaj[6],"\0");
    strcpy(punctaj[7],"\0");
    strcpy(punctaj[8],"JX");
    strcpy(punctaj[9],"\0");
    strcpy(punctaj[10],"QZ");

    for ( unsigned int i=0; i<strlen(cuvant); i++)
    {
        for ( int j=1; j<11; j++)
        {
            if(strchr(punctaj[j],cuvant[i])) 
                { 
                    *player=*player+j; 
                }
        }              
    }           
}

void adaugareCuvant (int coord1, int coord2, 
                    int dir, char cuvant[25], char gameboard[15][15])
{
    //adauga un cuvant in matrice

    for(unsigned int j = 0; j < strlen(cuvant); j++)
    {
            if (dir) // dir=1 => scriere pe coloana
                gameboard[coord1+j][coord2]=cuvant[j];
            else // dir=0 => scriere pe linie
                gameboard[coord1][coord2+j]=cuvant[j];
    }
}

int pctBns (int coord1, int coord2, int dir, 
                    char Seq1[25], char Seq2[25],char cuvant[25])
{
    //pctBns calculeaza pe care un cuvant il are, cu tot cu bonus

    int count1=0, count2=0;
    int punctajIntermediar=0;

    for ( unsigned int j = 0; j<strlen(cuvant); j++)
    {
        if (bonus_board[coord1][coord2]==1) 
        {
            if(strstr(cuvant,Seq1))
            {
                count1++;
            }
        }

            if (bonus_board[coord1][coord2]==2) 
            {   
                char *aux;
                //aux va devine adresa unde se gaseste Seq2 in cuvant
                aux=strstr(cuvant,Seq2);
                if(aux) //verificare ca aux exista 
                { 
                    if(strcmp(aux,Seq2)==0)
                    {
                        count2++;
                    }
                    
                
                }        
            }
            if(dir) 
                coord1++;
            else 
                coord2++;
    }   
        
        adaugarePunctaj(cuvant,&punctajIntermediar);

        for (int j=1; j<=count1; j++)
            punctajIntermediar=punctajIntermediar*2;
        for (int j=1; j<=count2; j++)
            punctajIntermediar=punctajIntermediar*3;

    return punctajIntermediar;

}

void citireCuvant (int *coord1, int *coord2, int *dir, char cuvant[25])
{
    //citeste un cuvant, impreuna cu coordonatele sale

    char buffer[50];
    char *p;
    char sep[10]=" ";

            fgets(buffer,50,stdin);
            p=strtok(buffer,sep);
            *coord1=atoi(p);
            
            p=strtok(NULL,sep);
            *coord2=atoi(p);
            
            p=strtok(NULL,sep);
            *dir=atoi(p);
            
            p=strtok(NULL,sep);
            strcpy(cuvant,p);
            cuvant[strlen(cuvant)-1]='\0';
}

void citireBoard(int n, int x[25], int y[25], int d[25], 
                    char lista[25][25], char gameboard[15][15])
{
    //functia citeste toata tabla de la input, si memoreaza fiecare cuvant in
    //vectorul lista,iar coordonatele lui in vectorii,x,y,d, si adauga in 
    //matricea gameboard cuvantile citite.

    int coord1,coord2,dir;
    char cuvant[25];

    for (int i=0; i<n; i++)
    {
        citireCuvant(&coord1,&coord2,&dir,cuvant);
        adaugareCuvant(coord1,coord2,dir,cuvant,gameboard);
        strcpy(lista[i],cuvant);
        x[i]=coord1;
        y[i]=coord2;
        d[i]=dir;
    }
}

void citireInit (char Seq1[25], char Seq2[25], int *n)
{
    //citeste primele 3 date: secventele bonus si numarul de cuvinte de citit

    char buffer[25];

    fgets(buffer,20,stdin);
    strcpy(Seq1,buffer);
    Seq1[strlen(Seq1)-1]='\0';

    fgets(buffer,20,stdin);
    strcpy(Seq2,buffer);
    Seq2[strlen(Seq2)-1]='\0';

    fgets(buffer,20,stdin);
    *n=atoi(buffer);
}

void task1 (char gameboard[15][15])
{
    //asemanator cu citireBoard, citeste si adauga elementele la matrice,
    //dar nu retine coordonatele.

    int  n, coord1, coord2, dir;
    char cuvant[25],buffer[25];
    
    fgets(buffer,20,stdin);
    n=atoi(buffer);

    for (int i = 0; i < n; i++)
    {
        citireCuvant(&coord1,&coord2,&dir,cuvant);
        adaugareCuvant(coord1,coord2,dir,cuvant,gameboard);
    } 

    print_board(gameboard);
}

void task2 ()
{
    //task2 calculeaza puntajele fara bonus. Din aceasta cauza am folosit
    //o citire diferita, unde ma folosesc doar de cuvinte,ignorand coordonatele

    int n, count=1, player1=0, player2=0;
    char buffer[25], cuvant[25];
    char *p;
    char sep[10]=" ";
    
    fgets(buffer,20,stdin);
    n=atoi(buffer);
   
    for (int i = 0; i < n; i++)
    {
        fgets(buffer,20,stdin);
        p=strtok(buffer,sep);

        //scap de coordonate
        while (p)
        {
            strcpy(cuvant,p);
            p=strtok(NULL,sep);
        }        

        if (count%2==1) 
            adaugarePunctaj(cuvant,&player1);
        else   
            adaugarePunctaj(cuvant,&player2);
            
        count++;
        }
    
    printf("Player 1: %d Points\n",player1);
    printf("Player 2: %d Points\n",player2);
}

void task3 (char gameboard[15][15]) 
{
    //task3 calculeaza punctajele bonus facand apel la pctBns

    char Seq1[25], Seq2[25],lista[25][25];
    int n,i,punctaj=0;
    int player1=0, player2=0;
    int coordx[25],coordy[25],direction[25];

    citireInit(Seq1,Seq2,&n);
    citireBoard(n,coordx,coordy,direction,lista,gameboard);

    for(i=0; i<n; i++)
    {
        punctaj=0;
        punctaj=pctBns(coordx[i],coordy[i],direction[i],Seq1,Seq2,lista[i]);

        if ((i+1)%2==1)
        {
            player1+=punctaj;
        }
        else
        {
            player2+=punctaj;
        }
    }

    printf("Player 1: %d Points\n",player1);
    printf("Player 2: %d Points\n",player2);
}

void cautareCuvant (int *coordx, int *coordy, int*direction,int *indice,
                     int n, char lista[25][25], char gameboard[15][15])
{
    int  adaugat=0;

    for(int k=*indice; k<100; k++)
   {
       if (adaugat==0)
       {
           int ok=1;

           for(int z=0; z<n; z++)
           {
               if(strcmp(lista[z],words[k])==0)
                {
                    ok=0;
                }
           }

           int i=0,j=0;
           for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    if(gameboard[i][j]==words[k][0] && ok==1)  
            {
                if (j+strlen(words[k])-1<15 && adaugat==0)
                {   
                    int ok1=1;
                
                    for(unsigned int v=1; v<strlen(words[k]); v++)
                        if(gameboard[i][j+v]!='.')
                        {
                            ok1=0;
                        }

                    if (ok1)
                    {   
                        *coordx=i;
                        *coordy=j;
                        *direction=0;
                        *indice=k;    
                        adaugat=1;
                    }
                }
                if (adaugat==0)
                {   
                    if (i+strlen(words[k])-1<15)
                    {
                        int ok1=1;
                
                        for(unsigned int v=1; v<strlen(words[k]); v++)
                            if(gameboard[i+v][j]!='.')
                                ok1=0;
                        if (ok1)
                        {
                            *coordx=i;
                            *coordy=j;
                            *direction=1;
                            *indice=k;
                            adaugat=1;
                        }
                    }
                }
            }
        }
   }

}

void cuvantOptim(int *coord1,int *coord2,int *dir, int *ind, int n,
                                int *max, char Seq1[25], char Seq2[25], 
                                char lista[25][25], char gameboard[15][15])
{
    int i,j;
    int punctaj;

    /*luam fiecare cuvant din words ce nu este pe tabla(echivalent in lista)
    si pentru fiecare pozitie posibila,
    calculam ce valoare va avea punctaj.
    memoram coordonatele si indicele cuvantului cu punctaj maximal.*/

    /*cautarile + verificarile sunt destul de imbricate,motivul pentru care nu
    am declarat niste functii sa faca verificarile cu if-urile este lista
    lunga de parametrii pe care acea functie ar avea-o, plus ca nu ar exista
    alte apeluri la aceasta functie*/

    for(int k=0; k<100; k++)
    {
        int ok=1;
        for(int z=0; z<n; z++)
           {
               if(strcmp(lista[z],words[k])==0)
                {
                    ok=0;
                }
           }
        if(ok)
        { 
            for(i=0;i<15;i++)
            {
                for (j=0;j<15;j++)
                {
                    if(gameboard[i][j]==words[k][0])
                    {
                        if(j+strlen(words[k])-1<15)
                        {
                            int ok1=1;
                
                            for(unsigned int v=1; v<strlen(words[k]); v++)
                                if(gameboard[i][j+v]!='.')
                                {
                                 ok1=0; 
                                }
                                
                            if(ok1)
                            {
                                punctaj=pctBns(i,j,0,Seq1,Seq2,words[k]);

                                if(punctaj>=*max)
                                {   
                                    if(punctaj==*max)
                                    {
                                        if(i<=*coord1)
                                        {
                                            if(i==*coord1)
                                            {
                                                if(j<*coord2)
                                                {
                                                    *coord1=i;
                                                    *coord2=j;
                                                    *dir=0;
                                                    *ind=k;
                                                    *max=punctaj; 
                                                }
                                            }
                                            else 
                                            {
                                                *coord1=i;
                                                *coord2=j;
                                                *dir=0;
                                                *ind=k;
                                                *max=punctaj;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        *coord1=i;
                                        *coord2=j;
                                        *dir=0;
                                        *ind=k;
                                        *max=punctaj;
                                    }
                                }
                            }
                        }

                        if(i+strlen(words[k])-1<15)
                        {
                            int ok1=1;
                            for(unsigned int v=1; v<strlen(words[k]); v++)
                                if(gameboard[i+v][j]!='.')
                                {
                                    ok1=0;
                                }

                            if(ok1)
                            {
                                punctaj=pctBns(i,j,1,Seq1,Seq2,words[k]);
                            
                                if(punctaj>=*max)
                                {   
                                    if(punctaj==*max)
                                    {
                                        if(i<=*coord1)
                                        {
                                            if(i==*coord1)
                                            {
                                                if(j<*coord2)
                                                {
                                                    *coord1=i;
                                                    *coord2=j;
                                                    *dir=1;
                                                    *ind=k;
                                                    *max=punctaj; 
                                                }
                                            }
                                            else 
                                            {
                                                *coord1=i;
                                                *coord2=j;
                                                *dir=1;
                                                *ind=k;
                                                *max=punctaj;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        *coord1=i;
                                        *coord2=j;
                                        *dir=1;
                                        *ind=k;
                                        *max=punctaj;
                                    }   
                                }
                            }
                        }
                    }
                }
            }       
        }
    }

}

void task4 (char gameboard[15][15])
{
    int n,coord1=20,coord2=20,dir,ind=0;
    char Seq1[25], Seq2[25], lista[25][25];
    int coordx[25],coordy[25],direction[25];

    citireInit(Seq1,Seq2,&n);
    citireBoard(n,coordx,coordy,direction,lista,gameboard);

    cautareCuvant(&coord1,&coord2,&dir,&ind,n,lista,gameboard);
    adaugareCuvant(coord1,coord2,dir,words[ind],gameboard);

    print_board(gameboard);
}

void task5 (char gameboard[15][15])
{
    /*spre deosebire de task4, nu se mai aplica acelasi reguli 
    ale amplasarii unui cuvant, aici fiind important doar pozitia 
    unde se obtine valoarea maxima a unui cuvant.*/

    char lista[25][25], Seq1[25], Seq2[25];
    int player1=0, player2=0,punctaj=0;
    int coord1=20, coord2=20, dir,ind=0;
    int n;
    int coordx[25],coordy[25],direction[25];
    int max=0;

    citireInit(Seq1,Seq2,&n);
    citireBoard(n,coordx,coordy,direction,lista,gameboard);

    //calculare punctaj pentru fiecare jucator

    for(int i=0; i<n; i++)
    {
        punctaj=0;
        punctaj=pctBns(coordx[i],coordy[i],direction[i],Seq1,Seq2,lista[i]);

        if ((i+1)%2==1)
        {
            player1=player1+punctaj;
        }
        else
        {
            player2=player2+punctaj;
        }
    }

    cuvantOptim(&coord1,&coord2,&dir,&ind,n,&max,Seq1,Seq2,lista,gameboard);
    
    if(max+player2>=player1)
    {
        adaugareCuvant(coord1,coord2,dir,words[ind],gameboard);
        print_board(gameboard);
    }
    else
    {
        printf("Fail!");
    }
}

void task6 (char gameboard[15][15])
{
    int coord1=20,coord2=20,dir,ind=0,n,max;
    char cuvant[25],lista[25][25],Seq1[15], Seq2[15];
    int player1=0, player2=0,punctaj=0;
    int len=0;

    citireInit(Seq1,Seq2,&n);
    
    for (int i=0; i<n; i++)
    {
        citireCuvant(&coord1,&coord2,&dir,cuvant);
        adaugareCuvant(coord1,coord2,dir,cuvant,gameboard);
        strcpy(lista[len++],cuvant);
        punctaj=pctBns(coord1,coord2,dir,Seq1,Seq2,cuvant);
        player2=player2+punctaj;
    
        max=0; coord1=20; coord2=20;
        cuvantOptim(&coord1,&coord2,&dir,&ind,len,
                    &max,Seq1,Seq2,lista,gameboard);
        adaugareCuvant(coord1,coord2,dir,words[ind],gameboard);
        strcpy(lista[len++],words[ind]);
        player1=player1+max;
    }

    print_board(gameboard);

    if (player1<player2)
    {
        printf("Player 1 Won!\n");
    }
    else 
    {
        printf("Player 2 Won!\n");
    }
}


int main () {

    char gameboard[15][15];
    char task[10];

    for (int i=0; i<15; i++)
        for(int j=0; j<15; j++)
            gameboard[i][j]='.';
            
    fgets(task, 10, stdin);

    switch (task[0]) 
    {
        case '0': 
            print_board(gameboard);
            break;
        case '1':
            task1(gameboard);
            break;
        case '2':
            task2();
            break;
        case '3':
            task3(gameboard);
            break;
        case '4':
            task4(gameboard);
            break;
        case '5':
            task5(gameboard);
            break;
        case '6':
            task6(gameboard);
            break;
    }
    return 0;
}