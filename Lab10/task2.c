#include <stdio.h>


struct song {
    int id;
    char name[30];
    char artist[30];
};


struct album {
    int id;
    int number_of_songs;
    int max_number_of_songs;
    struct song *songs;
};

struct album* allocAlbum (int id, int max_number_of_songs)
{

}

