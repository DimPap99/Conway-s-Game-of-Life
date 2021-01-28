#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#ifndef world
#define world
 //WORLD SIZES
const int SMALL_WIDTH = 20;
const int SMALL_HEIGHT = 20;
const int MEDIUM_WIDTH = 40;
const int MEDIUM_HEIGHT = 40;
const int LARGE_WIDTH = 80;
const int LARGE_HEIGHT = 80;
//AVAILABLE TRIBES

char* TRIBE0_UNICODE = "🔴"; //Until multiple tribes are implemented this one is considered ALIVE
char* TRIBE1_UNICODE = "🔵";
char* TRIBE2_UNICODE = "🔶";
char* TRIBE3_UNICODE = "🔷";
char* TRIBE4_UNICODE = "🔺";
char* DEAD_UNICODE = "⬛";

int rand_in_range(int min, int max){
    return rand() % (max + 1 - min) + min;
}

enum TRIBE_ENUM {DEAD = 0, TRIBE0 = 1, TRIBE1 = 2, TRIBE2 = 3, TRIBE3 = 4, TRIBE4 = 5};

typedef struct world_struct
{
    int width;
    int height;
    int turns;
    int tribes;
    int** world_map;
} w_strct;
typedef struct world_cell
{
    int row;
    int column;
}c_struct;


typedef struct neighbor_arr{
    int neighbor_index;
    enum TRIBE_ENUM max_tribe;
}neighbor_struct;

typedef struct change{
    int w_col;
    int w_row;
    enum TRIBE_ENUM tribe;
}change_struct;
void set_alive(int** array, int row, int col, int is_alive){
    array[row][col] = is_alive;
}
int is_alive(w_strct *w, int row, int col){
    if(w->world_map[row][col] == DEAD) return 0;
    else return w->world_map[row][col];
}
void print_map(w_strct w){
    for (int i=0; i<w.height; i++)
    {
        for (int j=0; j<w.width; j++)
        {   switch (w.world_map[i][j]){
                case DEAD:
                    printf(" %s ",DEAD_UNICODE);
                    break;
                case TRIBE0:
                    printf(" %s ",TRIBE0_UNICODE);
                    break;
                case TRIBE1:
                    printf(" %s ",TRIBE1_UNICODE);
                    break;
                case TRIBE2:
                    printf(" %s ",TRIBE2_UNICODE);
                    break;
                case TRIBE3:
                    printf(" %s ",TRIBE3_UNICODE);
                    break;
                case TRIBE4:
                    printf(" %s ",TRIBE4_UNICODE);
                    break;
                
        }
            
        }
        printf("%s","\n");
    }
    printf("%s","\n\n\n\n");
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
           
            int is_alive = rand() & 1; // spawn a dead or alive cell
            enum TRIBE_ENUM tribe;
            if(is_alive == 0){
                tribe = DEAD;
            }else{
                int numb;
                numb = 1;//rand_in_range(1,w->tribes); //generate different symbols depending on the tribe
                switch(numb){ // determine randomly the tribe each cell belongs to 
                    case 1:
                        tribe = TRIBE0;
                    break;
                    case 2:
                        tribe = TRIBE1;
                    break;
                    case 3:
                        tribe = TRIBE2;
                    break;
                    case 4:
                        tribe = TRIBE3;
                    break;
                    case 5:
                        tribe = TRIBE4;
                    break;
                    default:
                        tribe = TRIBE0;
                }
            }
        w->world_map[i][j] = tribe;
        
        }
    }

    
}

int find_valid_neighbors(c_struct *array, int current_row, int current_col, int world_width){
    
    //Depending on the position of our current cell (row,col) we have 8 different possibilities
    //So our array will have pre alocated memory for 8 cell structs 
    
    int count_neighbors = 0; //count_neighbors will act as an index we will also return it 
    //to iterate over our array later
    if(array != NULL){
        if(current_row - 1 >= 0){
            
            c_struct c;
            c.row = current_row - 1;
            c.column = current_col;
            array[count_neighbors] = c;
            count_neighbors++;
        }

        if(current_row + 1 <= world_width - 1){
            c_struct c;
            c.row = current_row + 1;
            c.column = current_col;
            c.column = current_col;
            array[count_neighbors] = c;
            if(array == NULL) return -1;
            count_neighbors++;
        }
        // printf("%d\n", count_neighbors);
        if(current_col + 1 <= world_width - 1){
            
            c_struct c;
            c.row = current_row;
            c.column = current_col + 1;
            array[count_neighbors] = c;
            count_neighbors++;
        }
     

//After the first 3 neighbors we start checking for memory realocation
         if(current_col - 1 >= 0){
             
             c_struct c;
            c.row = current_row;
            c.column = current_col - 1;
           
            array[count_neighbors]=c;
            count_neighbors++;
            
        }

         if(current_col + 1 <= world_width - 1 && current_row + 1 <= world_width - 1){
              
             c_struct c;
            c.row = current_row + 1;
            c.column = current_col + 1;
            c.column = current_col;
            array[count_neighbors] = c;

            count_neighbors++;
            
            
        }

        if(current_col - 1 >= 0 && current_row - 1 >= 0){
          
             c_struct c;
            c.row = current_row - 1;
            c.column = current_col - 1;
            c.column = current_col;
            array[count_neighbors] = c;

            count_neighbors++;
            
        }

        if(current_col - 1 >= 0 && current_row + 1 <= world_width - 1){
          
             c_struct c;
            c.row = current_row + 1;
            c.column = current_col  - 1;
            c.column = current_col;
            array[count_neighbors] = c;
            count_neighbors++;
            

        }

        if(current_col + 1 <= world_width - 1 && current_row - 1 >= 0){
           
             c_struct c;
            c.row = current_row - 1;
            c.column = current_col + 1;
           c.column = current_col;
            array[count_neighbors] = c;

            count_neighbors++;
            
        }

    return count_neighbors;
    }else return -1;

}

#endif