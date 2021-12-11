#pragma once


#include <QTimer>


#include "ghost.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


class Clyde : public Ghost
{
    Q_OBJECT


    public:

        Clyde(VaxMan* input_vaxmanPointer);
       ~Clyde();


    private:

        QTimer *timer;
};

