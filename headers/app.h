#pragma once


class Ghost;

class QGraphicsItem;
class QGraphicsView;


/* Edited by :  Melwyn Francis Carlo (2021) */


typedef enum
{
    BARRIER     = 1, 
    PATHWAY     = 2, 
    VAXDOT      = 3, 
    ENERGIZER   = 4, 
    BONUS_FRUIT = 5 

} Cell_Type;

enum
{
    WIDTH  = 608, 
    HEIGHT = 702, 

    MAX_ROWS = 21, 
    MAX_COLS = 19, 

    MAP_CELL_SIZE = 32 
};


void slot_multiply_ghosts();


void create_game(QGraphicsView *graphicsView);
void destroy_game();

void start_game();

void delete_ghost_entity(Ghost *ghostEntity);

void display_termination_message(const bool& gameWon);

bool is_pathway(const unsigned int& rowIndex, const unsigned int& colIndex);
bool is_barrier(const unsigned int& rowIndex, const unsigned int& colIndex);
bool is_within_boundary(const int& rowIndex, const int& colIndex);

Cell_Type get_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex);
void set_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex, Cell_Type cellType);
void unset_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex);

void add_graphics_item_to_scene(QGraphicsItem* graphicsItem);

