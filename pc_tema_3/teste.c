#include "bmp_header.h"
#include <stdio.h>
#include <cjson/cJSON.h>


int main () 
{

    /*char buffer[90000];
    struct json_object *parsed_json;
	struct json_object *name;
	struct json_object *age;
	struct json_object *friends;
	struct json_object *friend;
    struct json_object *structura;
    struct json_object *ceva;
	size_t n_friends;

    FILE *file = fopen("teste.json","r");
	fread(buffer, 90000, 1, file);
	fclose(file);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "friends", &friends);
    printf("%s\n", json_object_get_string(name) );

    n_friends = json_object_array_length(friends);
	printf("Found %lu friends\n",n_friends);

	for(int i=0;i<n_friends;i++) {
		friend = json_object_array_get_idx(friends, i);
		printf("%d. %s\n",i+1,json_object_get_string(friend));
	}


    printf("\n");

    json_object_object_get_ex(parsed_json, "structura", &structura);
    printf("%s\n",json_object_get_string(structura->camp1));*/

    
    cJSON *structura;
    cJSON *camp1;
    cJSON *camp2;
    cJSON *nume;
    cJSON *friends;
    cJSON *numFriends;
    cJSON *friend;
    cJSON *matrice;

    char buffer[90000];
    FILE *file = fopen("teste.json","r");
	fread(buffer, 90000, 1, file);
	fclose(file);

    cJSON *input =  cJSON_Parse(buffer);
    nume = cJSON_GetObjectItemCaseSensitive(input,"structura");
    char *string = cJSON_Print(nume);
    cJSON *input2 = cJSON_Parse(string);
    camp1 = cJSON_GetObjectItemCaseSensitive(input2,"camp1");
    camp2 = cJSON_GetObjectItemCaseSensitive(input2,"camp2");
    char *output = cJSON_Print(camp2);



    friends = cJSON_GetObjectItemCaseSensitive(input,"friends");


    friend = cJSON_GetArrayItem(friends,1);     
    output = cJSON_PrintUnformatted(friend);



    printf("%s\n", output);

    cJSON *vector = cJSON_GetObjectItemCaseSensitive(input,"matrice");
    cJSON *elemnt = cJSON_GetArrayItem(vector,1);
    int pri = elemnt->valueint;
    if(cJSON_IsNumber(elemnt)) printf("DA \n");
    printf("%d \n",pri);



    return 0;
}