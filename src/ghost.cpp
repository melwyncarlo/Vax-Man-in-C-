#include "ghost.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


Ghost::Ghost(VaxMan* input_vaxmanPointer, const unsigned int& input_rowPos, const unsigned int& input_colPos)
{
    rowPos = input_rowPos;
    colPos = input_colPos;

    vaxmanReference = input_vaxmanPointer;

    setPos(colPos * MAP_CELL_SIZE, rowPos * MAP_CELL_SIZE);
}


Ghost::~Ghost()
{
}


bool Ghost::is_ghost_dead()
{
    if (vaxmanReference->check_vaxman_intersection(rowPos, colPos) == true)
    {
        return true;
    }

    return false;
}


Ghost::Direction Ghost::get_random_direction( const Direction& dir1, 
                                              const Direction& dir2, 
                                              const Direction& dir3, 
                                              const Direction& dir4)
{
    Direction randomDirection;

    do
    {
        randomDirection = (Direction) ((rand() % 4) + 1);
    }
    while ((randomDirection == dir1) 
       ||  (randomDirection == dir2) 
       ||  (randomDirection == dir3) 
       ||  (randomDirection == dir4));

    return randomDirection;
}


Ghost::Direction Ghost::get_opposite_direction(const Direction& input_direction)
{
    if (input_direction == UP)
    {
        return DOWN;
    }
    else if (input_direction == DOWN)
    {
        return UP;
    }
    else if (input_direction == LEFT)
    {
        return RIGHT;
    }
    else /* if (input_direction == RIGHT) */
    {
        return LEFT;
    }
}


void Ghost::get_prioritized_directions(Direction (&directionsArray)[4])
{
    directionsArray [3] = get_opposite_direction(direction);
    directionsArray [0] = get_random_direction(directionsArray [3], NONE, NONE, NONE);
    directionsArray [1] = get_random_direction(directionsArray [3], directionsArray [0], NONE, NONE);
    directionsArray [2] = get_random_direction(directionsArray [3], directionsArray [0], directionsArray [1], NONE);
}


void Ghost::get_best_next_translation()
{
    Direction newDirections [4];

    get_prioritized_directions (newDirections);

    bool firstAvailable_changed = false;

    unsigned int firstAvailable_rowPos = rowPos;
    unsigned int firstAvailable_colPos = colPos;

    Direction firstAvailable_direction = direction;

    for (unsigned int i = 0; i < 4; i++)
    {
        if (newDirections [i] == UP)
        {
            if (is_within_boundary (rowPos - 1, colPos))
            {
                if (is_pathway (rowPos - 1, colPos))
                {
                    if ( ! firstAvailable_changed)
                    {
                        firstAvailable_changed   = true;
                        firstAvailable_direction = UP;
                        firstAvailable_rowPos--;
                    }

                    if (vaxmanReference->might_vaxman_intersect(rowPos, colPos, (VaxMan::Direction) direction))
                    {
                        direction = get_opposite_direction(UP);
                    }
                    else
                    {
                        direction = UP;
                        rowPos--;
                        return;
                    }
                }
            }
        }
        else if (newDirections [i] == DOWN)
        {
            if (is_within_boundary (rowPos + 1, colPos))
            {
                if (is_pathway (rowPos + 1, colPos))
                {
                    if ( ! firstAvailable_changed)
                    {
                        firstAvailable_changed   = true;
                        firstAvailable_direction = DOWN;
                        firstAvailable_rowPos++;
                    }

                    if (vaxmanReference->might_vaxman_intersect(rowPos, colPos, (VaxMan::Direction) direction))
                    {
                        direction = get_opposite_direction(DOWN);
                    }
                    else
                    
                    {
                        direction = DOWN;
                        rowPos++;
                        return;
                    }
                }
            }
        }
        else if (newDirections [i] == LEFT)
        {
            if (is_within_boundary (rowPos, colPos - 1))
            {
                if (is_pathway (rowPos, colPos - 1))
                {
                    if ( ! firstAvailable_changed)
                    {
                        firstAvailable_changed   = true;
                        firstAvailable_direction = LEFT;
                        firstAvailable_colPos--;
                    }

                    if (vaxmanReference->might_vaxman_intersect(rowPos, colPos, (VaxMan::Direction) direction))
                    {
                        direction = get_opposite_direction(LEFT);
                    }
                    else
                    
                    {
                        direction = LEFT;
                        colPos--;
                        return;
                    }
                }
            }
        }
        else if (newDirections [i] == RIGHT)
        {
            if (is_within_boundary (rowPos, colPos + 1))
            {
                if (is_pathway (rowPos, colPos + 1))
                {
                    if ( ! firstAvailable_changed)
                    {
                        firstAvailable_changed   = true;
                        firstAvailable_direction = RIGHT;
                        firstAvailable_colPos++;
                    }

                    if (vaxmanReference->might_vaxman_intersect(rowPos, colPos, (VaxMan::Direction) direction))
                    {
                        direction = get_opposite_direction(RIGHT);
                    }
                    else
                    
                    {
                        direction = RIGHT;
                        colPos++;
                        return;
                    }
                }
            }
        }
    }

    rowPos = firstAvailable_rowPos;
    colPos = firstAvailable_colPos;

    direction = firstAvailable_direction;
}


void Ghost::move_ghost()
{
    if (is_ghost_dead())
    {
        delete_ghost_entity(this);

        return;
    }

    get_best_next_translation();

    setPos (colPos * MAP_CELL_SIZE, rowPos * MAP_CELL_SIZE);
}

