#pragma once


#include <QGraphicsPixmapItem>


class QTimer;
class QKeyEvent;


/* Edited by :  Melwyn Francis Carlo (2021) */


class VaxMan : public QObject, public QGraphicsPixmapItem
{ 
    Q_OBJECT


    public:

        typedef enum
        {
            NONE  = 0, 

            UP    = 1, 
            DOWN  = 2, 
            LEFT  = 3, 
            RIGHT = 4 

        } Direction;

        VaxMan();
       ~VaxMan();

        void set_end_of_game();

        void keyPressEvent(QKeyEvent *event);

        bool might_vaxman_intersect( const unsigned int& ghost_rowIndex, 
                                     const unsigned int& ghost_colIndex, 
                                     const Direction& ghost_direction);

        bool check_vaxman_intersection(const unsigned int& rowIndex, const unsigned int& colIndex);


    public slots:

        void slot_move_vaxman();


    private:

        QTimer *timer;

        bool endOfGame;
        bool bonusFruitSet;

        unsigned int rowPos;
        unsigned int colPos;

        Direction direction;

        unsigned int currentScore;

        QGraphicsTextItem *scoreTextObject;


        void update_game();
};

