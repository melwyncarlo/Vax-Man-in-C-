#include "app.h"

#include "blinky.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


Blinky::Blinky(VaxMan* input_vaxmanPointer) : Ghost (input_vaxmanPointer, 8, 9)
{
    setPixmap(QPixmap(":/pics/blinky"));

    add_graphics_item_to_scene((QGraphicsItem *) this);

    direction = UP;

    timer = new QTimer(this);
    QObject::connect (timer, &QTimer::timeout, this, &Ghost::move_ghost);
    timer->start (400);
}


Blinky::~Blinky()
{
    delete timer;
}

