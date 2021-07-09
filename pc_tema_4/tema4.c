#include "utils.h"

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, 
										InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

//functii definite de mine pentru rezolvarea temei
char* alocareChar (int n)
{
	char *a = (char *) calloc(n+1,sizeof(char));

	if (a == NULL)
	{
		exit(101);
	}

	return a;
}

int difModul (int a, int b)
{
	if (a < b)
	{
		int aux = a;
		a = b;
		b = aux;
	}
	return a-b;
}

int fromChartoEnum (char a[200])
{
	if ( strcmp(a,"Rotator") == 0 )
	{
		return 0;
	}

	if ( strcmp(a,"Decoder") == 0 )
	{
		return 1;
	}

	if ( strcmp(a,"Invertor") == 0 )
	{
		return 2;
	}

	if ( strcmp(a,"Impostor") == 0 )
	{
		return 3;
	}

	return -1;
}

// Task 1
void *RotateMatrix(void *input)
{
	// TODO

    int n = *(int*)input;

	int matrice[250][250];
	int output[250][250];

	for ( int i = 1; i <= n; i++)
	{
		for (int  j = 1; j <= n; j++)
		{
			int cj = j;
			int p=1;

			while (cj > 0)
			{
				cj=cj/10;
				p=p*10;
			}

			matrice[i][j] =  i*p + j; // matricea de forma ij
		}
	}
	
	for ( int i = 1; i <= n; i++)
	{
		for (int  j = 1; j <= n; j++)
		{
			output[i][j] = matrice[n-j+1][i]; //matricea rotita
		}

	}

	int len=0;
	char *buffer = (char *) calloc(MAX_LEN_STR_OUT,sizeof(char));

	if (!buffer)
	{
		exit(101);
	}

    for ( int i = 1; i <= n; i++)
	{
		for (int  j = 1; j <= n; j++)
		{
		   sprintf(buffer+len,"%d ",output[i][j]);
		   len=strlen(buffer);
		}

		buffer[len]='\n';
		buffer[++len]='\0';
	}

	buffer[len-1]='\0'; // eliminare ultimu \n, cum se cere in cerinta

	return (void*)buffer;
}

// Task 2
void *DecodeString(void *input)
{
	// TODO
	char *string = (char *)input;
	char sep[] = "_";
	char *p;
	int nr, suma = 0;
	
	p = strtok (string,sep);

	while (p)
	{
		nr=atoi(p);
		suma = suma + nr; 
		p=strtok(NULL,sep);
	}

	char *rez = (char *) calloc(255,sizeof(char));

	if (!rez)
	{
		exit(101);
	}

	//transformare in string
	sprintf(rez,"%d",suma);

	return (void *) rez;
}

//Task 3
void *InvertArray(void *input)
{
	// TODO
	int n = *(int *)input; // n = numarul de elemente, mai usor de lucrat
	int *v = (int *)input;
	

	if ( n % 2 == 0)
	{
		for ( int i = 1; i <= n; i++)
		{
			//inversare 2 cate 2
			int aux;
			aux = v[i];
			v[i] = v[i+1];
			v[i+1] = aux;
			i++;
		}
	}
	else 
	{
		for( int i = 1; i <=n/2; i++)
		{
			// inversare totala
			int aux; 
			aux = v[i];
			v[i] = v[n - i + 1];
			v[n - i + 1] = aux;
		}
	}

	char *sir = alocareChar(MAX_LEN_STR_ATR);

	if (!sir)
	{
		exit(101);
	}

	char buffer[250];
	int len=0;

	//transformare in string
	for (int i = 1; i <= n; i++)
	{
		sprintf(buffer,"%d ",v[i]);
		strcpy(sir+len,buffer);
		len=strlen(sir);
	}

	return (void *)sir;
}

//Task 4
Player *allocPlayer()
{
	// TODO
	Player *playerStructura = (Player *) calloc(1,sizeof(Player));

	if (!playerStructura)
	{
		exit(101);
	}

	playerStructura->alive = 1;
	playerStructura->name = alocareChar(MAX_LEN_STR_ATR);
	playerStructura->hat = alocareChar(MAX_LEN_STR_ATR);
	playerStructura->color = alocareChar(MAX_LEN_STR_ATR);

	return playerStructura;
}

//Task 4
Game *allocGame()
{
	// TODO
	Game *gameStructura = (Game *) calloc(1,sizeof(Game));

	if (!gameStructura)
	{
		exit(101);
	}

	gameStructura->name = alocareChar(MAX_LEN_STR_ATR);

	return gameStructura;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	// TODO
	Player* player = allocPlayer ();
	int n;
	fscanf(inputFile,"%s",player->name);
	fscanf(inputFile,"%s",player->color);
	fscanf(inputFile,"%s",player->hat);
	fscanf(inputFile,"%d ",&n);

	player->numberOfLocations = n;
	player->locations = (Location *) calloc(2*n,sizeof(Location));

	if (!player->locations)
	{
		exit(101);
	}

	player->indexOfLocation = 0; // initializare pe prima locatie

	for ( int i=0; i<n; i++)
	{
		int x,y;
		fscanf(inputFile,"(%d,%d) ",&x,&y);
		
		player->locations[i].x = x;
		player->locations[i].y = y;
	}

	char role[50];
	fscanf(inputFile,"%s",role);

	player->playerRole = fromChartoEnum(role);

	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	// TODO

	Game *game = allocGame ();
	fscanf(inputFile,"%s",game->name);
	fscanf(inputFile,"%d",&game->killRange);
	fscanf(inputFile,"%d",&game->numberOfCrewmates);

	int n = game->numberOfCrewmates;

	game->crewmates = (Player **) calloc(n,sizeof(Player*));

	for ( int i=0; i<n; i++)
	{
		game->crewmates[i] = ReadPlayer (inputFile);
	}

	game->impostor = ReadPlayer (inputFile);
	
	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	// TODO

	fprintf(outputFile,"Player %s ",player->name);
	fprintf(outputFile,"with color %s, ",player->color);
	fprintf(outputFile,"hat %s ",player->hat);

	char *role = fromEnumtoString(player->playerRole);
	fprintf(outputFile,"and role %s ", role);

	fprintf(outputFile,"has entered the game.\n");
	fprintf(outputFile,"Player's locations: ");
	
	for (int i = 0; i < player->numberOfLocations; i++)
	{
		fprintf(outputFile,"(%d,",player->locations[i].x);
		fprintf(outputFile,"%d) ",player->locations[i].y);
	}
	fprintf(outputFile,"\n");

	free(role);
	
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	// TODO

	fprintf(outputFile,"Game %s has just started!\n", game->name);
	fprintf(outputFile,"	Game options:\n");
	fprintf(outputFile,"Kill Range: %d\n",game->killRange);
	fprintf(outputFile,"Number of crewmates: %d\n",game->numberOfCrewmates);
	fprintf(outputFile,"\n");
	fprintf(outputFile,"	Crewmates:\n");

	for (int i = 0; i < game->numberOfCrewmates; i++)
	{
		WritePlayer(game->crewmates[i],outputFile);
	}

	fprintf(outputFile,"\n	Impostor:\n");
	WritePlayer(game->impostor,outputFile);

	return;
}

//Task 7
void *KillPlayer(void *input)
{
	// TODO
	Game *game = (Game*) input;

	int distance;
	int message = 0;
	int minDistance = game->killRange +1;
	int indice;

	char *kill = alocareChar(MAX_LEN_STR_ATR);
	strcpy(kill,"Impostor ");
	strcat(kill,game->impostor->name);


	for (int i = 0; i < game->numberOfCrewmates; i++)
	{
		if (game->crewmates[i]->alive == 1)
		{
			int xKiller, yKiller,pozKiller;
			pozKiller = game->impostor->indexOfLocation;
			xKiller = game->impostor->locations[pozKiller].x;
			yKiller = game->impostor->locations[pozKiller].y;
			
			int xCrew, yCrew,pozCrew;
			pozCrew = game->crewmates[i]->indexOfLocation;
			xCrew = game->crewmates[i]->locations[pozCrew].x;
			yCrew = game->crewmates[i]->locations[pozCrew].y;

			distance = difModul(xKiller,xCrew) + difModul(yKiller,yCrew);

			if (distance <= minDistance && distance <= game->killRange)
			{
				minDistance = distance;
				message = 1;
				indice = i;
			}
		}
	}
	
	if (message)
	{
		strcat(kill," has just killed crewmate ");
		strcat(kill,game->crewmates[indice]->name);
		strcat(kill," from distance ");
		
		char buffer[255];
		sprintf(buffer,"%d",minDistance);
		strcat(kill,buffer);
		strcat(kill,".");
		game->crewmates[indice]->alive=0;
	}
	else
	{
		strcat(kill," couldn't kill anybody.");
	}

	return (void *)kill;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	// TODO

	for (int i = 0; i < game->numberOfCrewmates; i++)
	{

		if (game->crewmates[i]->alive == 0) //traieste jucatorul ?
		{
			fprintf(outputFile,"Crewmate %s is dead.\n",game->crewmates[i]->name);
		}
		else
		{
			game->crewmates[i]->indexOfLocation++;//avansarea pozitie
			int x, y, contorLocatii = game->crewmates[i]->indexOfLocation;

			//verificare pentru a face ciclu prin pozitii
			if (contorLocatii >= game->crewmates[i]->numberOfLocations)
			{
				contorLocatii = 0;
				game->crewmates[i]->indexOfLocation = 0;
			}

			//coordonatele jucatorului, pentru a evita liniile prea lungi
			x = game->crewmates[i]->locations[contorLocatii].x;
			y = game->crewmates[i]->locations[contorLocatii].y;

			fprintf(outputFile,"Crewmate %s ",game->crewmates[i]->name);
			fprintf(outputFile,"went to location (%d,%d).\n",x,y);
			fprintf(outputFile,"Crewmate %s's ",game->crewmates[i]->name);

			int role = game->crewmates[i]->playerRole;
			
			char *output = Abilities[role](inputMatrix[i]);
			fprintf(outputFile,"output:\n%s\n",output);
			free(output);
		}
	}

	game->impostor->indexOfLocation++;//avansarea pozitie
	int x, y, contorLocatii = game->impostor->indexOfLocation;
	//coordonatele impostorului, pentru a evita liniile prea lungi

	//verificare pentru a face ciclu prin pozitii
	if (contorLocatii >= game->impostor->numberOfLocations)
		{
			contorLocatii = 0;
			game->impostor->indexOfLocation = 0;
		}

	x = game->impostor->locations[contorLocatii].x;
	y = game->impostor->locations[contorLocatii].y;
	
	fprintf(outputFile,"Impostor %s went to location ",game->impostor->name);
	fprintf(outputFile,"(%d,%d).\n",x,y);
	fprintf(outputFile,"Impostor %s's output:\n",game->impostor->name);

	int role = game->impostor->playerRole;
	char *rez = Abilities[role](game);
	fprintf(outputFile,"%s\n",rez);

	free(rez);

	return;
}

// Task 9
void FreePlayer(Player *player)
{
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);

	return;
}

// Task 9
void FreeGame(Game *game)
{
	// TODO

	for (int i = 0; i < game->numberOfCrewmates; i++)
	{
		FreePlayer(game->crewmates[i]);
		free(game->crewmates[i]);
	}

	free(game->crewmates);
	FreePlayer(game->impostor);
	free(game->impostor);
	free(game->name);
	free(game);

	return;
}