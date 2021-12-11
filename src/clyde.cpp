#include <cmath>

#include "app.h"

#include "clyde.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


Clyde::Clyde(VaxMan* input_vaxmanPointer) : Ghost (input_vaxmanPointer, 9, 8)
{
    setPixmap(QPixmap(":/pics/clyde"));

    add_graphics_item_to_scene((QGraphicsItem *) this);

    direction = RIGHT;

    timer = new QTimer(this);
    QObject::connect (timer, &QTimer::timeout, this, &Ghost::move_ghost);
    timer->start (400);
}


Clyde::~Clyde()
{
    delete timer;
}

