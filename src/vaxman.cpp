#include <time.h>

#include <QFont>
#include <QTimer>
#include <QKeyEvent>

#include "app.h"

#include "vaxman.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


VaxMan::VaxMan()
{
    rowPos = 15;
    colPos =  9;

    direction = NONE;

    endOfGame     = false;
    bonusFruitSet = false;

    currentScore = 0;

    scoreTextObject = new QGraphicsTextItem();

    setPixmap(QPixmap(":/pics/vaxmanLeft"));

    setPos(colPos * MAP_CELL_SIZE, rowPos * MAP_CELL_SIZE);

    add_graphics_item_to_scene(this);
    add_graphics_item_to_scene(scoreTextObject);

    scoreTextObject->setDefaultTextColor(0x00ffffff);
    scoreTextObject->setFont(QFont("times", 15));
    scoreTextObject->setPlainText("SCORE: " + QString::number(currentScore));
    scoreTextObject->setPos(10, HEIGHT - 30);

    srand(time(0));

    timer = new QTimer(this);
    QObject::connect (timer, &QTimer::timeout, this, &VaxMan::slot_move_vaxman);
    timer->start (300);
}


VaxMan::~VaxMan()
{
    delete scoreTextObject;
    delete timer;
}


void VaxMan::update_game()
{
    const unsigned int BONUS_FRUIT_ACTIVATION_SCORE = 500;

    if ((currentScore >= BONUS_FRUIT_ACTIVATION_SCORE) && ! bonusFruitSet)
    {
        bonusFruitSet = true;

        set_map_cell(15, 9, BONUS_FRUIT);
    }

    if (get_map_cell(rowPos, colPos) == BONUS_FRUIT)
    {
        unset_map_cell(rowPos, colPos);

        const unsigned int FRUIT_BONUS_INCREMENTAL_SCORE = 200;

        currentScore += FRUIT_BONUS_INCREMENTAL_SCORE;
    }

    if (get_map_cell(rowPos, colPos) == VAXDOT)
    {
        unset_map_cell(rowPos, colPos);

        const unsigned int INCREMENTAL_SCORE = 10;

        currentScore += INCREMENTAL_SCORE;
    }

    if (get_map_cell(rowPos, colPos) == ENERGIZER)
    {
        unset_map_cell(rowPos, colPos);

        const unsigned int ENERGIZER_BONUS_INCREMENTAL_SCORE = 100;

        currentScore += ENERGIZER_BONUS_INCREMENTAL_SCORE;
    }
}


void VaxMan::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
    {
        direction = UP;
        setPixmap(QPixmap(":/pics/vaxmanUp"));
    }

    else if (event->key() == Qt::Key_Down)
    {
        direction = DOWN;
        setPixmap(QPixmap(":/pics/vaxmanDown"));
    }

    else if (event->key() == Qt::Key_Left)
    {
        direction = LEFT;
        setPixmap(QPixmap(":/pics/vaxmanLeft"));
    }

    else if (event->key() == Qt::Key_Right)
    {
        direction = RIGHT;
        setPixmap(QPixmap(":/pics/vaxmanRight"));
    }
}


void VaxMan::slot_move_vaxman()
{
    const int MAXIMUM_SCORE = 1500;

    scoreTextObject->setPlainText("SCORE: " + QString::number(currentScore));

    if ((currentScore >= MAXIMUM_SCORE) && ! endOfGame)
    {
        display_termination_message(true);

        endOfGame = true;
    }

    update_game();

    if (direction == UP)
    {
        if (rowPos == 0)
        {
            if (is_barrier (MAX_ROWS - 1, colPos) == false) rowPos = MAX_ROWS - 1;
        }
        else
        {
            if (is_barrier (rowPos - 1, colPos) == false) rowPos--;
        }
    }

    if (direction == DOWN)
    {
        if (rowPos == MAX_ROWS - 1)
        {
            if (is_barrier (0, colPos) == false) rowPos = 0;
        }
        else
        {
            if (is_barrier (rowPos + 1, colPos) == false) rowPos++;
        }
    }

    if (direction == LEFT)
    {
        if (colPos == 0)
        {
            if (is_barrier (rowPos, MAX_COLS - 1) == false) colPos = MAX_COLS - 1;
        }
        else
        {
            if (is_barrier (rowPos, colPos - 1) == false) colPos--;
        }
    }

    if (direction == RIGHT)
    {
        if (colPos == MAX_COLS - 1)
        {
            if (is_barrier (rowPos, 0) == false) colPos = 0;
        }
        else
        {
            if (is_barrier (rowPos, colPos + 1) == false) colPos++;
        }
    }

    setPos(colPos * MAP_CELL_SIZE, rowPos * MAP_CELL_SIZE);
}


bool VaxMan::might_vaxman_intersect( const unsigned int& ghost_rowIndex, 
                                     const unsigned int& ghost_colIndex, 
                                     const Direction& ghost_direction)
{
    if (ghost_direction == UP)
    {
        if ((ghost_colIndex == colPos) && ((ghost_rowIndex - rowPos) < 3))
        {
            return true;
        }
    }
    else if (ghost_direction == DOWN)
    {
        if ((ghost_colIndex == colPos) && ((rowPos - ghost_rowIndex) < 3))
        {
            return true;
        }
    }
    else if (ghost_direction == LEFT)
    {
        if ((ghost_rowIndex == rowPos) && ((ghost_colIndex - colPos) < 3))
        {
            return true;
        }
    }
    else if (ghost_direction == RIGHT)
    {
        if ((ghost_rowIndex == rowPos) && ((colPos - ghost_colIndex) < 3))
        {
            return true;
        }
    }

    return false;
}


bool VaxMan::check_vaxman_intersection(const unsigned int& rowIndex, const unsigned int& colIndex)
{
    if ( ! endOfGame && (rowIndex == rowPos) && (colIndex == colPos)) return true;

    return false;
}


void VaxMan::set_end_of_game()
{
    endOfGame = true;
}

