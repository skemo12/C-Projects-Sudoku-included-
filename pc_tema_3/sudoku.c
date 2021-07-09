#include "src/bmp_header.h"
#include <stdio.h>
#include "src/cJSON.h"
#include "src/cJSON.c"

typedef struct Zeros
{
    // Structura folosita pentru completarea spatiilor goale din joc

    int pozitions; // pozitia unde e trebuie completat
    int complexity; //Complexitatea de completare cea mai mica
    int rowOrColumn;// unde se gaseste complexitatea, pe coloana sau linie
    int total;
} Zeros;

typedef struct Data
{
    // Structura folosita pentru lucrul cu imaginea, variabile utile

    int bitmapSize;
    int rows;
    int colums; 
    int bits; //bts per line
    int ls;  // line size
    int firstCorner; //first possible writable corner 
    int dblc;  //distance between square's line points
    int dbnc; //distance between square' side points
}Data;

Data getData (bmp_infoheader infoHeader)
{
    // Preia si calculeaza valorile necesare

    Data data;
    data.bitmapSize = infoHeader.biSizeImage;
    data.rows = infoHeader.height;
    data.colums = infoHeader.width;
    data.bits = infoHeader.bitPix/8;
    data.ls = infoHeader.height*3;
    data.firstCorner = 2*data.ls + 2*data.bits;
    data.dblc = data.ls*((data.colums - 10)/9 +1); 
    data.dbnc = ((data.rows - 10)/9 +1)*data.bits; 

    return data;
}

int verificareActiv (int *array, int poz)
{
    // Verificam daca un pixel este alb sau nu

    if (array[poz] + array[poz+1] + array[poz+2] != 3*255)
    {
        return 1;
    }
    
    return 0;
}

int decodificare (int codificare[10])
{
    // Decodificare , transforma laturile cheie in cifra

    if (codificare[1] == 0 && codificare[2] == 0 && codificare[3] == 0)
    {
        if (codificare[6] == 1 && codificare[7] == 1 && codificare[3] == 0)
        {
            return 1;
        }
    }

    if(codificare[4] == 0 && codificare[5]==1 && codificare[7] == 0)
    {
        return 2;
    }

    if(codificare[4] == 0 && codificare[5]== 0 && codificare[2] == 1)
    {
        return 3;
    }

    if(codificare[4] == 1 && codificare[5]== 0 && codificare[1] == 0)
    {
        return 4;
    }

    if(codificare[4] == 1 && codificare[5]== 0 && codificare[1] == 1)
    {
        if (codificare[6] == 0 && codificare[1] == 1 && codificare[3] == 1)
        {
            return 5;
        }
    }

    if(codificare[4] == 1 && codificare[5]== 1 && codificare[6] == 0)
    {
        if (codificare[7] == 1 && codificare[1] == 1 && codificare[3] == 1)
        {
            return 6;
        }
    }

    if(codificare[4] == 0 && codificare[5]== 0 && codificare[1] == 1)
    {
        return 7;
    }
    
    if(codificare[4] == 1 && codificare[5]== 1 && codificare[6] == 1)
    {
        if (codificare[7] == 1 && codificare[1] == 1 && codificare[3] == 1)
        {
            return 8;
        }
    }

    if(codificare[4] == 1 && codificare[5]== 0 && codificare[6] == 1)
    {
        if (codificare[7] == 1 && codificare[1] == 1 && codificare[3] == 1)
        {
            return 9;
        }
    }


   

    return 0;
}

int *codificare(int x)
{
    // Codificare, tranforma cifrele in laturi cheie

    int *codificare = (int *) calloc(10, sizeof(int));

    if (!codificare)
    {
        exit (404);
    }
    
    for (int i = 0; i < 10; i++)
    {
        codificare[i] = 0;
    }
    

    if (x == 1)
    {
        codificare[6] = 1;
        codificare[7] = 1;
    }

    if (x == 2)
    {
        codificare[1] = 1;
        codificare[2] = 1;
        codificare[3] = 1;
        codificare[5] = 1;
        codificare[6] = 1;
    }

    if (x == 3)
    {
        codificare[1] = 1;
        codificare[2] = 1;
        codificare[3] = 1;
        codificare[6] = 1;
        codificare[7] = 1;
    }

    if (x == 4)
    {
        codificare[2] = 1;
        codificare[4] = 1;
        codificare[6] = 1;
        codificare[7] = 1;
    }

    if (x == 5)
    {
        codificare[1] = 1;
        codificare[2] = 1;
        codificare[3] = 1;
        codificare[4] = 1;
        codificare[7] = 1;
    }

    if (x == 6)
    {
        codificare[1] = 1;
        codificare[2] = 1;
        codificare[3] = 1;
        codificare[4] = 1;
        codificare[5] = 1;
        codificare[7] = 1;
    }

    if (x == 7)
    {
        codificare[1] = 1;
        codificare[6] = 1;
        codificare[7] = 1;
    }

    if (x == 8)
    {
        for (int i = 0; i < 8; i++)
        {
            codificare[i] = 1;
        }
        
    }

    if (x == 9)
    {
        for (int i = 0; i < 8; i++)
        {
            codificare[i] = 1;
        }

        codificare[5] = 0;
    }
    
    return codificare;
    
}

int *calculatePoz (int ref, Data data)
{
    // Calculeaza pozitiile cheie

    int *laturi = (int *) calloc(8,sizeof(int));

    if (!laturi)
    {
        exit (404);
    }
  
    int widthInSquare = ((data.colums - 10)/9 + 1)/2;
    widthInSquare = widthInSquare * 3;
    int heightInSquare = ((data.rows-10)/9 - 1)/3;
    heightInSquare = heightInSquare * 3;
    laturi[1] = ref + 2*data.bits;
    laturi[2] = ref + data.ls*2 + heightInSquare;
    laturi[3] = ref + data.ls*4 + heightInSquare;
    laturi[4] = ref + data.ls;
    laturi[5] = ref + data.ls*3;
    laturi[6] = ref + data.ls + widthInSquare;
    laturi[7] = ref + data.ls*3 + widthInSquare;

    return laturi;
}

Zeros *calculateComplexity (int numarNedet, int **sudokuTable)
{
    // Calculeaza si retine pozitiile si complexitatile elementelor nule

    int indexPoz = 0;
    Zeros *zeros = (Zeros *) calloc(numarNedet,sizeof(Zeros));

    if (!zeros)
    {
        exit (404);
    }
  
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudokuTable[i][j] == 0)
            {
                zeros[indexPoz].pozitions = i*10+j;

                int min1 = 0, min2 = 0;
                for (int k = 0; k < 9; k++)
                {
                    if (sudokuTable[i][k] == 0)
                    {
                        min1++;
                    }
                    if (sudokuTable[k][j] == 0)
                    {
                        min2++;
                    }
                }
                if (min1<min2)
                {   
                    zeros[indexPoz].rowOrColumn = 0;
                    zeros[indexPoz].complexity = min1;
                }
                else
                {
                    zeros[indexPoz].rowOrColumn = 1;
                    zeros[indexPoz].complexity = min2;
                }
                
                indexPoz++;
            }
        }
    }

    return zeros;
}

int verificareTabla (int **tablaSudoku)
{
    // Verifica daca tabla este completata corect

    int ok = 1;
    //vectori de aparitii
    int vectorAparitiiLinie[10];
    int vectorAparitiiColoane[10];

    //verificare fiecare linie si coloana
    for (int i = 0; i < 9; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            vectorAparitiiLinie[j] = 0;
        }

        for (int j = 1; j < 10; j++)
        {
            vectorAparitiiColoane[j] = 0;
        }
        
        for (int j = 0; j < 9; j++)
        {
            int indice = tablaSudoku[i][j];
            vectorAparitiiLinie[indice]++;

            indice = tablaSudoku[j][i];
            vectorAparitiiColoane[indice]++;
        }

        for (int j = 1; j < 10; j++)
        {
            if (vectorAparitiiLinie[j] != 1 || vectorAparitiiColoane[j]!= 1)
            {
                ok = 0;
            }
        }
        
    }

    //verificare fiecare subpatrat
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 1; k < 10; k++)
            {
                vectorAparitiiLinie[k] = 0;
            }

            for (int k = 0; k < 3; k++)
            {
                for (int z = 0; z < 3; z++)
                {
                    int indice = tablaSudoku[i*3+k][j*3+z];
                    vectorAparitiiLinie[indice]++;
                }
                
            }
            
            for (int k = 1; k < 10; k++)
            {
                if (vectorAparitiiLinie[k] != 1)
                {
                    ok = 0;
                }
            }

        }
        
    }
    
    return ok;
    
}

int ComplexityOne (int **sudokuTable, int poz, int rowOrColumn)
{
    // Cauta ce numar trebuie pus intr-un spatiu gol de complexitate 1

    int cifre[11];
    int x = poz/10;
    int y = poz%10;

    for (int i = 0; i < 10; i++)
    {
        cifre[i] = 0;
    }
    
    if (rowOrColumn == 1)
    {
        for (int i = 0; i < 9; i++)
        {
            int index = sudokuTable[i][y];
            cifre[index]++;
        }

        for (int i = 1; i <= 9; i++)
        {
            if (cifre[i] == 0)
            {
                return i;
            }
        }
    } 
    else
    {
        for (int i = 0; i < 9; i++)
        {
            int index = sudokuTable[x][i];
            cifre[index]++;
        }

        for (int i = 1; i <= 9; i++)
        {
            if (cifre[i] == 0)
            {
                return i;
            }
        }
    }
    return 0;
}

void addLeftRight (int *bitmap, int poz, Data data)
{
    // Adding a vertical line

    int times = (data.rows - 10)/9; // how many pixels in a square
    times = times - 2; // -2 for white space between line and digit
    times = times/2; // we separated the full horizontal line in 2 keypoints

    for (int i = 0; i < times; i++)
    {
        bitmap[poz + i*data.ls] = 255;
        bitmap[poz + 1 + i*data.ls] = 0;
        bitmap[poz + 2 + i*data.ls] = 255;
    }
    
    for (int i = 0; i < times; i++)
    {
        bitmap[poz - i*data.ls] = 255;
        bitmap[poz + 1 - i*data.ls] = 0;
        bitmap[poz + 2 - i*data.ls] = 255;
    }
}

void addUpMiddleDown (int *bitmap, int poz, Data data)
{
    // Adding a full horizontal line

    int times = (data.colums - 10)/9; 
    times = times - 2; // -2 for white space between line and digit
    times = times/2; // the keypoint is exactly at the middle => i<=times

    for (int i = 0; i <= times; i++)
    {
        bitmap[poz + i*data.bits] = 255;
        bitmap[poz + 1 + i*data.bits] = 0;
        bitmap[poz + 2 + i*data.bits] = 255;
    }
    
    for (int i = 0; i <= times; i++)
    {
        bitmap[poz - i*data.bits] = 255;
        bitmap[poz + 1 - i*data.bits] = 0;
        bitmap[poz + 2 - i*data.bits] = 255;
    }
}

void createOutputName (char outputFile[255], char extension[50], char *input)
{
    // Creates output file name
    char *board = strstr(input, "board");
    strcat(outputFile, "_");
    strcat(outputFile, board);
    outputFile[20] = '\0';
    strcat(outputFile, extension);
}

int **createSudoku (int *bitmap, Data data)
{
    //Converts bmp img to a 9x9 matrix

    int ref = data.firstCorner;
    int codificare[10];

    int **tablaSudoku = (int **) calloc(9, sizeof(int*));

    if (!tablaSudoku)
    {
        exit (404);
    }
  
    for (int i = 0; i < 9; i++)
    {
        tablaSudoku[i] = (int *) calloc(9, sizeof(int));

        if (!tablaSudoku[i])
        {
            exit (404);
        }
  
    }
    
    for (int i = 0; i < 9; i++)
    {

        for (int j = 0; j < 9; j++)
        {
            ref = data.firstCorner + i*data.dblc + j*data.dbnc;
            int *laturi = calculatePoz(ref, data);

            for (int k = 0; k < 10; k++)
            {
                codificare[k] = 0;
            }
            
            for (int k = 1; k < 8; k++)
            {
                codificare[k] = verificareActiv(bitmap, laturi[k]);
            }

            tablaSudoku[i][j] = decodificare(codificare);
            free(laturi);
            
        }

    }
    
    return tablaSudoku;
}

int *convertJSONArrayToIntArray (cJSON *bitmap)
{
    int size = cJSON_GetArraySize(bitmap);
    int *array =(int *) calloc(size, sizeof(int));

    if (!array)
    {
        exit (404);
    }
  

    for (int i = 0; i < size; i++)
    {
        cJSON *value = cJSON_GetArrayItem(bitmap, i);
        array[i] = value->valueint;
    }
    
    return array;
}

int *convertJSONArrayToKeyPoints (cJSON *bitmap, Data data)
{
    // Function to convert only key points to int array for task3
    int size = cJSON_GetArraySize (bitmap);
    int *array = (int *) calloc(size, sizeof(int));

    if (!array)
    {
        exit (404);
    }
  
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int ref = data.firstCorner + i*data.dblc + j*data.dbnc;
            int *laturi = calculatePoz(ref, data);
            for (int k = 1; k < 4; k++)
            {
                cJSON *value = cJSON_GetArrayItem(bitmap, laturi[k]);
                array[laturi[k]] = value->valueint;

                value = cJSON_GetArrayItem(bitmap, laturi[k] + 1);
                array[laturi[k] + 1] = value->valueint;

                value = cJSON_GetArrayItem(bitmap, laturi[k] + 2);
                array[laturi[k] + 2] = value->valueint;
            }

            cJSON *value = cJSON_GetArrayItem(bitmap, laturi[4]);
            array[laturi[6]] = value->valueint;
            
            value = cJSON_GetArrayItem(bitmap, laturi[4] + 1);
            array[laturi[6] + 1] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[4] +2);
            array[laturi[6] + 2] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[5]);
            array[laturi[7]] = value->valueint;
            
            value = cJSON_GetArrayItem(bitmap, laturi[5] + 1);
            array[laturi[7] + 1] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[5] +2);
            array[laturi[7] + 2] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[6]);
            array[laturi[4]] = value->valueint;
            
            value = cJSON_GetArrayItem(bitmap, laturi[6] + 1);
            array[laturi[4] + 1] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[6] +2);
            array[laturi[4] + 2] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[7]);
            array[laturi[5]] = value->valueint;
            
            value = cJSON_GetArrayItem(bitmap, laturi[7] + 1);
            array[laturi[5] + 1] = value->valueint;

            value = cJSON_GetArrayItem(bitmap, laturi[7] +2);
            array[laturi[5] + 2] = value->valueint;

            free(laturi);
            
        }
        
    }
    
    
    return array;
}

int **Backtraking (int **sudokuTable, Zeros *zeros, int numarNedet)
{
    // Daca sunt cazuri cu o grad de nederminare mai mare ca 1
    // Metoda backtracking - slow but works

    int last = numarNedet-1;
    int **solutions = (int **) calloc(numarNedet, sizeof(int*));

    if (!solutions)
    {
        exit (404);
    }
  
    for (int i = 0; i < numarNedet; i++)
    {
        solutions[i] = (int *) calloc(10, sizeof(int));

        if (!solutions[i])
        {
        exit (404);
        }
  
        for (int j = 0; j < 10; j++)
        {
            solutions[i][j] = j;
        }
        
    }
    

    while (verificareTabla(sudokuTable) != 1)
    {
        for (int i = 0; i < numarNedet; i++)
        {
            int x = zeros[i].pozitions/10;
            int y = zeros[i].pozitions%10;
            int indexSolutions = solutions[i][0];

            if (zeros[i].complexity != 0)
            {
                sudokuTable[x][y] = solutions[i][indexSolutions];
            }
        }

        solutions[last][0]++;
        int cn = last;

        while (solutions[cn][0] == 10 && cn > 0)
        {
            solutions[cn][0] = 0;
            cn--;
            solutions[cn][0]++;
        }

        
        if (solutions[0][0] == 10 && solutions[numarNedet -1][0] == 10)
        {
            break;
        }
        
    }

    for (int i = 0; i < numarNedet; i++)
    {
        free(solutions[i]);
    }

    free(solutions);

    return sudokuTable;
}

cJSON *initializare (char *filename)
{
    // Gets full cJSON file data

    FILE *file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    double count = ftell(file);
    char *buffer = (char *) calloc(count + 1, sizeof(char));

    if (!buffer)
    {
        exit (404);
    }
  
    fseek(file, 0, SEEK_SET);
    fread(buffer, count, 1, file);
    fclose(file);

    cJSON *input =  cJSON_Parse(buffer);

    free(buffer);

    return input;
}

bmp_fileheader *fileHeaderGet (cJSON *info)
{
    // Gets file header from JSON

    cJSON *fileHeader = cJSON_GetObjectItemCaseSensitive(info, "file_header");
    cJSON *signature;
    signature = cJSON_GetObjectItemCaseSensitive(fileHeader, "signature");
    cJSON *fileSize;
    fileSize = cJSON_GetObjectItemCaseSensitive(fileHeader, "file_size");
    cJSON *reserved = cJSON_GetObjectItemCaseSensitive(fileHeader, "reserved");
    cJSON *offset = cJSON_GetObjectItemCaseSensitive(fileHeader, "offset");

    bmp_fileheader *fileHeaderBmp;
    fileHeaderBmp = (bmp_fileheader *) calloc(1, sizeof(bmp_fileheader));

    if (!fileHeader)
    {
        exit (404);
    }
  

    fileHeaderBmp->fileMarker1 = signature->valuestring[0];
    fileHeaderBmp->fileMarker2 = signature->valuestring[1];
    fileHeaderBmp->bfSize = fileSize->valueint;
    fileHeaderBmp->imageDataOffset = offset->valueint;
    fileHeaderBmp->unused1 = reserved->valueint;

    return fileHeaderBmp;
}

bmp_infoheader *infoHeaderGet (cJSON *info)
{
    // Gets info header from JSON

    cJSON *infoHeader = cJSON_GetObjectItemCaseSensitive(info, "info_header");
    cJSON *size = cJSON_GetObjectItemCaseSensitive(infoHeader, "size");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(infoHeader, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(infoHeader, "height");
    cJSON *planes = cJSON_GetObjectItemCaseSensitive(infoHeader, "planes");
    cJSON *bitCount;
    bitCount = cJSON_GetObjectItemCaseSensitive(infoHeader, "bit_count");
    cJSON *compression;
    compression = cJSON_GetObjectItemCaseSensitive(infoHeader, "compression");
    cJSON *imageSize;
    imageSize = cJSON_GetObjectItemCaseSensitive(infoHeader, "image_size");
    cJSON *xPpm;
    xPpm = cJSON_GetObjectItemCaseSensitive(infoHeader, "x_pixels_per_meter");
    cJSON *yPpm;
    yPpm = cJSON_GetObjectItemCaseSensitive(infoHeader, "y_pixels_per_meter");
    cJSON *colors;
    colors = cJSON_GetObjectItemCaseSensitive(infoHeader, "colors_used");
    cJSON *clrImp;
    clrImp = cJSON_GetObjectItemCaseSensitive(infoHeader, "colors_important");

    bmp_infoheader *infoHeaderbmp;
    infoHeaderbmp = (bmp_infoheader *) calloc(1, sizeof(bmp_infoheader));


    if (!infoHeaderbmp)
    {
        exit (404);
    }
  

    infoHeaderbmp->biSize = size->valueint;
    infoHeaderbmp->width = width->valueint;
    infoHeaderbmp->height = height->valueint;
    infoHeaderbmp->planes = planes->valueint;
    infoHeaderbmp->bitPix = bitCount->valueint;
    infoHeaderbmp->biCompression = compression->valueint;
    infoHeaderbmp->biSizeImage = imageSize->valueint;
    infoHeaderbmp->biXPelsPerMeter = xPpm->valueint;
    infoHeaderbmp->biYPelsPerMeter = yPpm->valueint;
    infoHeaderbmp->biClrUsed = colors->valueint;
    infoHeaderbmp->biClrImportant = clrImp->valueint;

    return infoHeaderbmp;
}

bmp_fileheader fileHeaderRead (FILE *inputFile)
{
    // Reads fileheader from bmp file

    bmp_fileheader fileHeader;

    fread(&fileHeader.fileMarker1, 1, 1, inputFile);
    fread(&fileHeader.fileMarker2, 1, 1, inputFile);
    fread(&fileHeader.bfSize, 4, 1, inputFile);
    fread(&fileHeader.unused1, 4, 1, inputFile);
    fread(&fileHeader.imageDataOffset, 4, 1, inputFile);

    return fileHeader;
}

bmp_infoheader infoHeaderRead (FILE *inputFile)
{
    // Reads info header from bmp file
    bmp_infoheader infoHeader;

    fread(&infoHeader.biSize, 4,1, inputFile);
    fread(&infoHeader.width, 4, 1, inputFile);
    fread(&infoHeader.height, 4, 1, inputFile);
    fread(&infoHeader.planes, 2, 1, inputFile);
    fread(&infoHeader.bitPix, 2, 1, inputFile);
    fread(&infoHeader.biCompression, 4, 1, inputFile);
    fread(&infoHeader.biSizeImage, 4, 1, inputFile);
    fread(&infoHeader.biXPelsPerMeter, 4, 1, inputFile);
    fread(&infoHeader.biYPelsPerMeter, 4, 1, inputFile);
    fread(&infoHeader.biClrUsed, 4, 1, inputFile);
    fread(&infoHeader.biClrImportant, 4, 1, inputFile);

    return infoHeader;
}

int *bitmapRead (Data data, FILE *inputFile, int offset)
{
    // Reads bitmap from bmp file, excludes padding
    int padding = 0, paddingCount = 0;
    int line = data.rows;
    int *bitmap = (int *) calloc(data.bitmapSize, sizeof(int));

    if (!bitmap)
    {
        exit (404);
    }
  
    fseek(inputFile, offset, SEEK_SET);

    for (int i = 0; i < data.bitmapSize; i++)
    {   
        int index = line*data.rows*data.bits-data.ls+paddingCount;
        fread(&bitmap[index], 1, 1, inputFile);
        paddingCount++;

        if (paddingCount == data.ls)
        {
            paddingCount = 0;
            fread(&padding, 1, 1, inputFile);
            line--;
        } 
    }

    return bitmap;
}

void writeFileHeader (bmp_fileheader *fileHeader, FILE *output)
{
    // Writes file header to bmp output

    fwrite(&fileHeader->fileMarker1, 1, 1, output);
    fwrite(&fileHeader->fileMarker2, 1, 1, output);
    fwrite(&fileHeader->bfSize, 4, 1, output);
    fwrite(&fileHeader->unused1, 4, 1, output);
    fwrite(&fileHeader->imageDataOffset, 4, 1, output);
}

void writeInfoHeader (bmp_infoheader *infoHeader, FILE *output)
{
    // Writes info header to bmp output

    fwrite(&infoHeader->biSize, 4, 1, output);
    fwrite(&infoHeader->width, 4, 1, output);
    fwrite(&infoHeader->height, 4, 1, output);
    fwrite(&infoHeader->planes, 2, 1, output);
    fwrite(&infoHeader->bitPix, 2, 1, output);
    fwrite(&infoHeader->biCompression, 4, 1, output);
    fwrite(&infoHeader->biSizeImage, 4, 1, output);
    fwrite(&infoHeader->biXPelsPerMeter, 4, 1, output);
    fwrite(&infoHeader->biYPelsPerMeter, 4, 1, output);
    fwrite(&infoHeader->biClrUsed, 4, 1, output);
    fwrite(&infoHeader->biClrImportant, 4,1, output);
}

void writeBits (int *bitmap, FILE *output, Data data)
{
    // Scrierea bitilor pentru task1

    int index =0;
    int line = data.rows;
    int padding = 0;


    for (int i = 0; i < data.rows * data.colums * data.bits; i++)
    {           
        fwrite(&bitmap[line*data.rows*3-data.ls+index], 1, 1, output);
        index++;

        if(index == 219)
        {  
            index=0;
            line--;
            fwrite(&padding, 1, 1, output);
        }
    }
}

void writeBits2 (int *bitmap, FILE *output, Data data)
{
    // Scrierea bitilor pentru a repara greseala lui Emperor, task2

    int dull = 0;

    for (int i = data.rows -1; i >= 0; i--)
    {   
        for (int j = 0; j < 9; j++) //every square
        {
            //the line delimiting
            fwrite(&bitmap[i*data.rows*data.bits+j*data.dbnc], 1, 1,output);
            fwrite(&bitmap[i*data.rows*data.bits+j*data.dbnc+1], 1, 1,output);
            fwrite(&bitmap[i*data.rows*data.bits+j*data.dbnc+2], 1, 1,output);

            for (int k = 7; k > 0; k--) //inside of a square
            {
                for (int z = 0; z < 3; z++) // every 3 bits
                {
                    //writing letter in reverse
                    fwrite(&bitmap[i*73*3+j*24+k*3+z],1, 1, output);
                }
                
            }
            
        }
        //the last vertical pixels forming the black line
        for (int j = 0; j < 3; j++)
        {
            fwrite(&bitmap[i*data.rows*data.bits+data.ls+j-3], 1, 1, output);
        }

        fwrite(&dull, 1, 1, output);
        
    }
}

void createBMP (char *filename, cJSON *info)
{   
    // Construieste imaginea bmp conform task1

    FILE *output = fopen(filename,"wb");

    bmp_fileheader *fileHeader = fileHeaderGet(info);
    bmp_infoheader *infoHeader = infoHeaderGet(info);
    Data data = getData(*infoHeader);

    writeFileHeader(fileHeader,output);
    writeInfoHeader(infoHeader,output);
    cJSON *map = cJSON_GetObjectItemCaseSensitive(info, "bitmap");
    int *bitmap = convertJSONArrayToIntArray(map);
    writeBits(bitmap, output, data);

    free(fileHeader);
    free(infoHeader);
    free(bitmap);

    fclose(output);

}

void createBMP2 (char *filename, cJSON *info)
{
    // Construieste imaginea bmp conform task2 

    FILE *output = fopen(filename,"wb");

    bmp_fileheader *fileHeader = fileHeaderGet(info);
    bmp_infoheader *infoHeader = infoHeaderGet(info);
    Data data = getData(*infoHeader);

    writeFileHeader(fileHeader, output);
    writeInfoHeader(infoHeader, output);
    cJSON *map = cJSON_GetObjectItemCaseSensitive(info,"bitmap");
    int *bitmap = convertJSONArrayToIntArray(map);
    writeBits2(bitmap, output, data);

    free(fileHeader);
    free(infoHeader);
    free(bitmap);

    fclose(output);
}

int *completeTable (Data data, int *bitmap, int **sudokuTable,
                                    Zeros *zeros, int numarNedet)
{   
    // Completeaza tabla de joc cu cifrele gasite

    for (int i = 0; i < numarNedet; i++)
    {
        int x = zeros[i].pozitions/10;
        int y = zeros[i].pozitions%10;

        int ref = data.firstCorner + x*data.dblc+y*data.dbnc;
        int *laturi = calculatePoz(ref, data);
        int valueToAdd = sudokuTable[x][y];
        int *codificari = codificare(valueToAdd);

        for (int j = 1; j < 4; j++)
        {
            if (codificari[j] == 1)
            {
                addUpMiddleDown(bitmap, laturi[j],data);
            }
        }
        
        for (int j = 4; j < 8; j++)
        {
            if (codificari[j] == 1)
            {
                addLeftRight(bitmap, laturi[j],data);
            }
        }

        free(laturi);
        free(codificari);
    }

    return bitmap;
}

void task3 (cJSON *info,char *filename)
{
    FILE *output = fopen(filename, "wb");
    cJSON *bitmap = cJSON_GetObjectItemCaseSensitive(info, "bitmap");
    bmp_infoheader *infoHeader = infoHeaderGet(info);
    Data data = getData(*infoHeader);
    int *array = convertJSONArrayToKeyPoints(bitmap, data);
    
    int **sudokuTable = createSudoku(array, data);
    
    int ok = verificareTabla(sudokuTable);

    cJSON *jsonfile = cJSON_CreateObject();

    char *boardnumber = strstr(filename, "board");
    cJSON_AddStringToObject(jsonfile, "input_file", boardnumber);

    if (ok)
    {
        cJSON_AddStringToObject(jsonfile, "game_state","Win!");
    }
    else
    {
        cJSON_AddStringToObject(jsonfile, "game_state","Loss :(");
    }

    char *buffer = cJSON_Print(jsonfile);
    fprintf(output, "%s\n", buffer);

    cJSON_Delete(jsonfile);
  
    for (int i = 0; i < 9; i++)
    {
        free(sudokuTable[i]);
    }

    free(infoHeader);
    free(buffer);
    free(sudokuTable);
    free(array);
    fclose(output);
}

void task4 (char *inputFileName, char *outputFileName)
{
    FILE *inputFile = fopen(inputFileName,"rb");
    FILE *outputFile = fopen(outputFileName,"wb");

    bmp_fileheader fileHeader = fileHeaderRead(inputFile);
    bmp_infoheader infoHeader = infoHeaderRead(inputFile);
    Data data = getData(infoHeader);

    int *bitmap = bitmapRead(data,inputFile, fileHeader.imageDataOffset);
    int **sudokuTable = createSudoku(bitmap, data);
    int numarNedet = 0; //nr de spatii goale 

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudokuTable[i][j] == 0)
            {
                numarNedet++; 
            }
        }
    }
    
    Zeros *zeros = calculateComplexity(numarNedet, sudokuTable);

    for (int i = 0; i < numarNedet; i++)
    {
        if (zeros[i].complexity == 1)
        {
            int x = zeros[i].pozitions/10;
            int y = zeros[i].pozitions%10;
            int pozitions = zeros[i].pozitions;
            int rowOrColumns = zeros[i].rowOrColumn;
            int sol = ComplexityOne(sudokuTable, pozitions, rowOrColumns);
            sudokuTable[x][y] = sol;
            zeros[i].complexity = 0;
        }
    }
    
    if (verificareTabla(sudokuTable) != 1)
    {
        sudokuTable = Backtraking(sudokuTable, zeros, numarNedet);
    }
    
    bitmap = completeTable (data, bitmap, sudokuTable, zeros, numarNedet);

    writeFileHeader(&fileHeader,outputFile);
    writeInfoHeader(&infoHeader,outputFile);
    writeBits(bitmap,outputFile,data);

    for (int i = 0; i < 9; i++)
    {
        free(sudokuTable[i]);
    }
    
    free(zeros);
    free(sudokuTable);
    free(bitmap);
    fclose(inputFile);
    fclose(outputFile);
}

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        exit (122);
    }
     

    for (int i=0; i <(int) strlen(argv[2]); i++)
    {
        char outputFileName[255];
        strcpy(outputFileName,"output_task");
        cJSON *input = NULL;
        
        switch (argv[2][i])
        {
        case '1':
            input =  initializare(argv[1]);
            strcat(outputFileName,"1");
            createOutputName(outputFileName,".bmp",argv[1]);
            createBMP(outputFileName,input);
            cJSON_Delete(input);      
            break;
        case '2':
            input =  initializare(argv[1]);
            strcat(outputFileName,"2");
            createOutputName(outputFileName,".bmp",argv[1]);
            createBMP2(outputFileName,input);
            cJSON_Delete(input);
            break;
        case '3':
            input =  initializare(argv[1]);
            strcat(outputFileName,"3");
            createOutputName(outputFileName,".json",argv[1]);
            task3(input,outputFileName);
            cJSON_Delete(input);
            break;
        case '4':
            strcat(outputFileName,"4");
            createOutputName(outputFileName,".bmp",argv[1]);
            task4(argv[1], outputFileName);
            break;
        default:
            break;
        }
    }  
    
    return 0;

}