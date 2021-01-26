#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "world.h"

void print_world_info(w_strct w){
    printf("World Information: \nWidth: %d\nHeight: %d\nTurns: %d\nTribes: %d\n", w.width, w.height, w.turns, w.tribes);
}



int read_int(char* str){
    char *end;  
    int number;
    char buf[1000];
    do {
        if (!fgets(buf, sizeof buf, stdin))
            break;
        buf[strlen(buf) - 1] = 0;
        number = strtol(buf, &end, 10);
    } while (end != buf + strlen(buf));
    printf(str, number);
    return number;
    
}

void play_turn(w_strct *w){
    int neighbor_index = 0;
    for(int row = 0; row < w->height; row++){
        for(int col = 0; col < w->height;row++){
            c_struct* neighbors = malloc(8 * sizeof(c_struct)); 
            neighbor_index = find_valid_neighbors(neighbors, row, col, w->height);
        }
    }

}

w_strct init_game(w_strct *w){
    printf("Welcome to the Game of Life. \n");
    printf("How many turns do you want the simulation to run?");
    int turns = read_int("The game will run for %d turns...\n");
    w->turns = turns;
    printf("Choose the world size: \n1.Press 0 for small.\n2.Press 1 for medium.\n3.Press 2 for large. ");
    int world_size = read_int("You picked world size %d...\n");
    printf("Choose the number of tribes you want the world to contain. Available range 1-5: ");
    int tribes = read_int("The world will contain %d tribes...\n");
    if (tribes < 1 || tribes > 5) tribes = 1; //default
    w->tribes = tribes;
    switch(world_size){
        case 0:
        w->height = SMALL_HEIGHT;
        w->width = SMALL_WIDTH;
        break;

        case 1:
        w->height = MEDIUM_HEIGHT;
        w->width = MEDIUM_WIDTH;
        break;

        case 2:
        w->height = LARGE_HEIGHT;
        w->width = LARGE_WIDTH;
        break;

        default:
        w->height = MEDIUM_HEIGHT;
        w->width = MEDIUM_WIDTH;
        break;
    }    
    init_world_map(w);
}


int main(int argc, char *arv[]){
    w_strct w;
    w_strct *w_ptr = &w;
    w_strct world_struct = init_game(w_ptr);
    print_map(w);    
    c_struct* a = malloc(8 * sizeof(c_struct)); 
    int array_index = find_valid_neighbors(a, 1, 1, 10);
    free(a);
    free(w.world_map);
    // printf("%d", a[0].row);

    return 0;
}