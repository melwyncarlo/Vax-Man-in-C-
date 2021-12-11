#pragma once


#include <QTimer>


#include "ghost.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


class Pinky : public Ghost
{
    Q_OBJECT


    public:

        Pinky(VaxMan* input_vaxmanPointer);
       ~Pinky();


    private:

        QTimer *timer;
};

