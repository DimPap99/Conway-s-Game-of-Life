#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "world.h"
#include <unistd.h>
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
    //RULES:
    // Any live cell with two or three live neighbours survives.
    // Any dead cell with three live neighbours becomes a live cell.
    // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
    // New rule: A cell with more neighbors of a different tribe gets converted into that tribe. If that cell also has 3 
    //neighbors of the same tribes it dies.
void play_turn(w_strct *w){
    int neighbor_index = 0;
    change_struct *changes_array = malloc((w->height * w->width) * sizeof(change_struct));
    int changes_size = 0;
   
    for(int row = 0; row < w->height; row++){
        for(int col = 0; col < w->height;col++){
            c_struct* neighbors = malloc(8 * sizeof(c_struct));
            neighbor_index = find_valid_neighbors(neighbors, row, col, w->height);
            int same_tribe_neighbors = 0; //Same tribe or not dead
            int different_tribe_neighbors = 0;
            
           enum TRIBE_ENUM current_cell_tribe = w->world_map[row][col];
            for(int i=neighbor_index; i >= 0; i--){
                enum TRIBE_ENUM neighbor_tribe = w->world_map[neighbors[i].row][neighbors[i].column]; //get current neighbors tribe
                
                if(neighbor_tribe != DEAD){
                    if(neighbor_tribe == TRIBE0) same_tribe_neighbors++;
                    //else different_tribe_neighbors++;
                }

            }
            free(neighbors);
            if(current_cell_tribe == DEAD && same_tribe_neighbors == 3){
                change_struct change;
                change.w_row = row;
                change.w_col = col;
                change.tribe = TRIBE0;
                changes_array[changes_size] = change;
                changes_size++;
                
            }else if (current_cell_tribe != DEAD && (same_tribe_neighbors == 2 || same_tribe_neighbors == 3)){
                change_struct change;
                change.w_row = row;
                change.w_col = col;
                change.tribe = TRIBE0;
                changes_array[changes_size] = change;
                changes_size++;
                
            }else if(current_cell_tribe == TRIBE0 || current_cell_tribe == DEAD){
                change_struct change;
                change.w_row = row;
                change.w_col = col;
                change.tribe = DEAD;
                changes_array[changes_size] = change;
                changes_size++;
            }

        }
    }
        for(int i = 0; i < changes_size;i++){
            w->world_map[changes_array[i].w_row][changes_array[i].w_col] = changes_array[i].tribe;
        }
        free(changes_array);
        print_map(*w);
        

}

void init_game(w_strct *w){
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
    init_game(w_ptr);
    print_map(w);    
    for(int i = 0; i<w.turns;i++){
        play_turn(w_ptr);
        sleep(1);}
    free(w.world_map);

    return 0;
}