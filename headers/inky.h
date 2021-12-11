#pragma once


#include <QTimer>


#include "ghost.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


class Inky : public Ghost
{
    Q_OBJECT


    public:

        Inky(VaxMan* input_vaxmanPointer);
       ~Inky();


    private:

        QTimer *timer;
};

