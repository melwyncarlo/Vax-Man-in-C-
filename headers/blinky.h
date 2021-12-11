#pragma once


#include <QTimer>


#include "ghost.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


class Blinky : public Ghost
{
    Q_OBJECT


    public:

        Blinky(VaxMan* input_vaxmanPointer);
       ~Blinky();


    private:

        QTimer *timer;
};

