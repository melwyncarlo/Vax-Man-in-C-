#include "app.h"

#include "pinky.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


Pinky::Pinky(VaxMan* input_vaxmanPointer) : Ghost (input_vaxmanPointer, 9, 9)
{
    setPixmap(QPixmap(":/pics/pinky"));

    add_graphics_item_to_scene((QGraphicsItem *) this);

    direction = UP;

    timer = new QTimer(this);
    QObject::connect (timer, &QTimer::timeout, this, &Ghost::move_ghost);
    timer->start (400);
}


Pinky::~Pinky()
{
    delete timer;
}

