#include <QIcon>
#include <QApplication>
#include <QGraphicsView>

#include "app.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


int main(int argc, char *argv[])
{
    QApplication vaxmanApplication(argc, argv);

    vaxmanApplication.setWindowIcon(QIcon(":/pics/appIcon"));

    QCoreApplication::setApplicationName("Melly the Vax-Man");

    QGraphicsView *gameApp = new QGraphicsView();

    gameApp->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameApp->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameApp->setFixedSize(WIDTH + 5, HEIGHT + 5);

    gameApp->setSceneRect(0, 0, WIDTH, HEIGHT);

    create_game(gameApp);

    gameApp->show();

    start_game();

    return vaxmanApplication.exec();
}

