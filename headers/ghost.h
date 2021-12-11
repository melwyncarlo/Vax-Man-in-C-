#pragma once


#include <QGraphicsPixmapItem>

#include "app.h"
#include "vaxman.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


class Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT


    public:

        Ghost(VaxMan* input_vaxmanPointer, const unsigned int& input_rowPos, const unsigned int& input_colPos);

       ~Ghost();


    public slots:

        void move_ghost();


    protected:

        typedef enum
        {
            NONE  = 0, 

            UP    = 1, 
            DOWN  = 2, 
            LEFT  = 3, 
            RIGHT = 4 

        } Direction;

        unsigned int rowPos;
        unsigned int colPos;

        Direction direction;

        VaxMan *vaxmanReference;


    private:

        bool is_ghost_dead();

        Direction get_random_direction( const Direction& dir1, 
                                        const Direction& dir2, 
                                        const Direction& dir3, 
                                        const Direction& dir4);

        Direction get_opposite_direction(const Direction& input_direction);

        void get_best_next_translation();
        void get_prioritized_directions(Direction (&directionsArray)[4]);
};

