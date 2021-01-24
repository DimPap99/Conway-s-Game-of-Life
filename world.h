#include <stdlib.h>
#include <stdio.h>
#ifndef world
#define world

const int SMALL_WIDTH = 20;
const int SMALL_HEIGHT = 20;

const int MEDIUM_WIDTH = 40;
const int MEDIUM_HEIGHT = 40;


const int LARGE_WIDTH = 80;
const int LARGE_HEIGHT = 80;



typedef struct world_struct
{
    int width;
    int height;
    int turns;
    int tribes;
    int** world_map;
} w_strct;

typedef struct cell_node
{
    int row;
    int col;
    int is_alive;
} cell;

void set_alive(int** array, int row, int col, int is_alive){
    array[row][col] = is_alive;
}




void print_map(w_strct w){
    for (int i=0; i<w.height; i++)
    {
        for (int j=0; j<w.width; j++)
        {
            printf("%d",w.world_map[i][j]);
        }
        printf("%s","\n");
    }
}

void init_world_map(w_strct *w){
    w->world_map = malloc(w->height * sizeof *w->world_map);
    for (int i=0; i<w->height; i++)
    {
        w->world_map[i] = malloc(w->width * sizeof * w->world_map[i]);
    }
    for (int i=0; i<w->height; i++)
    {
        for (int j=0; j<w->width; j++)
        {
        w->world_map[i][j] = rand() & 1;
        
        }
    }

    
}

#endif