#include <QList>
#include <QTimer>
#include <QMediaPlayer>
#include <QGraphicsView>
#include <QMediaPlaylist>
#include <QGraphicsPixmapItem>

#include "app.h"
#include "inky.h"
#include "clyde.h"
#include "pinky.h"
#include "blinky.h"
#include "vaxman.h"


/* Edited by :  Melwyn Francis Carlo (2021) */


static QTimer *timer;

static Cell_Type           **objectMap;
static QGraphicsPixmapItem **imageMap;

static QGraphicsView  *view;
static QGraphicsScene *scene;

static VaxMan *vaxman;

static QList <Inky   *>   inkiesList;
static QList <Clyde  *>   clydesList;
static QList <Pinky  *>  pinkiesList;
static QList <Blinky *> blinkiesList;

static QMediaPlayer   *musicPlayer;
static QMediaPlaylist *musicPlaylist;

static QGraphicsTextItem *terminationMessage_entity;


static const unsigned int MAXIMUM_NUMBER_OF_GHOSTS = 32;


static void create_game_map()
{
    for (int row = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            if (objectMap [row] [col] == BARRIER)
            {
                 imageMap [row] [col].setPixmap(QPixmap(":/pics/barrier"));

                 imageMap [row] [col].setPos(col * MAP_CELL_SIZE, row * MAP_CELL_SIZE);

                scene->addItem (&(imageMap [row] [col]));
            }

            if (objectMap [row] [col] == VAXDOT)
            {
                 imageMap [row] [col].setPixmap(QPixmap(":/pics/vaxdot"));

                 imageMap [row] [col].setPos(col * MAP_CELL_SIZE, row * MAP_CELL_SIZE);

                scene->addItem (&(imageMap [row] [col]));
            }

            if (objectMap [row] [col] == ENERGIZER)
            {
                 imageMap [row] [col].setPixmap(QPixmap(":/pics/energizer"));

                 imageMap [row] [col].setPos(col * MAP_CELL_SIZE, row * MAP_CELL_SIZE);

                scene->addItem (&(imageMap [row] [col]));
            }
        }
    }
}


void create_game(QGraphicsView *graphicsView)
{
    const int INITIAL_MAP [MAX_ROWS] [MAX_COLS] = 
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
        { 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1 }, 
        { 1, 4, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 4, 1 }, 
        { 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 }, 
        { 1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1 }, 
        { 1, 3, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1 }, 
        { 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1 }, 
        { 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2 }, 
        { 1, 1, 1, 1, 3, 1, 2, 1, 1, 2, 1, 1, 2, 1, 3, 1, 1, 1, 1 }, 
        { 1, 2, 2, 2, 3, 2, 2, 1, 2, 2, 2, 1, 2, 2, 3, 2, 2, 2, 1 }, 
        { 1, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1 }, 
        { 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2 }, 
        { 1, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1 }, 
        { 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1 }, 
        { 1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 3, 1 }, 
        { 1, 4, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 4, 1 }, 
        { 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1 }, 
        { 1, 3, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1 }, 
        { 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1 }, 
        { 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 }, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
    };

    objectMap = new Cell_Type *[MAX_ROWS];
     imageMap = new QGraphicsPixmapItem *[MAX_ROWS];

    for (int row = 0; row < MAX_ROWS; row++)
    {
        objectMap [row] = new Cell_Type [MAX_COLS];
         imageMap [row] = new QGraphicsPixmapItem [MAX_COLS];

        for (int col = 0; col < MAX_COLS; col++)
        {
            objectMap [row] [col] = (Cell_Type) INITIAL_MAP [row] [col];
        }
    }

    view  = new QGraphicsView();
    scene = new QGraphicsScene();

    graphicsView->setScene(scene);

    create_game_map();

    graphicsView->setStyleSheet("background-color:#1C1C1C;");

    musicPlaylist = new QMediaPlaylist();
    musicPlaylist->addMedia(QUrl("qrc:/audio/themeSong"));
    musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    musicPlayer = new QMediaPlayer();
    musicPlayer->setPlaylist(musicPlaylist);

    terminationMessage_entity = nullptr;
}


void destroy_game()
{
    delete view;
    delete scene;

    for (auto inkyEntity : inkiesList)
    {
        delete inkyEntity;
    }

    for (auto clydeEntity : clydesList)
    {
        delete clydeEntity;
    }

    for (auto pinkyEntity : pinkiesList)
    {
        delete pinkyEntity;
    }

    for (auto blinkyEntity : blinkiesList)
    {
        delete blinkyEntity;
    }

    delete vaxman;

    delete musicPlayer;
    delete musicPlaylist;

    for (int row = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            delete  imageMap [row];
            delete objectMap [row];
        }
    }

    delete  imageMap;
    delete objectMap;

    if (timer != nullptr) delete timer;

    if (terminationMessage_entity != nullptr) delete terminationMessage_entity;
}


void start_game()
{
    vaxman = new VaxMan();
    vaxman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    vaxman->setZValue(100.0);
    vaxman->setFocus();

      inkiesList.push_back (new   Inky(vaxman));
      clydesList.push_back (new  Clyde(vaxman));
     pinkiesList.push_back (new  Pinky(vaxman));
    blinkiesList.push_back (new Blinky(vaxman));

    musicPlayer->play();

    timer = new QTimer();
    QObject::connect (timer, &QTimer::timeout, slot_multiply_ghosts);
    timer->start (30000);
}


void display_termination_message(const bool& gameWon)
{
    vaxman->set_end_of_game();

    vaxman->setPos(0, 0);

    terminationMessage_entity = new QGraphicsTextItem();

    QString terminationMessage_string_variable;

    if (gameWon)
    {
        terminationMessage_string_variable = QString("#AFD095;\">YOU'VE WON!");
    }
    else
    {
        terminationMessage_string_variable = QString("#FFAA95;\">YOU'VE LOST!");
    }

    QString terminationMessage_string_static_1 = 
    QString("<div style=\"background: #1C1C1C; color: ");

    QString terminationMessage_string_static_2 = 
    QString("</div>");

    terminationMessage_entity->setFont(QFont("mono", 50));

    terminationMessage_entity->setHtml(         terminationMessage_string_static_1 
                                        .append(terminationMessage_string_variable) 
                                        .append(terminationMessage_string_static_2));

    terminationMessage_entity->setPos(85, HEIGHT / 2 - 50);

    scene->addItem(terminationMessage_entity);

    scene->removeItem(vaxman);
}


void add_graphics_item_to_scene(QGraphicsItem* graphicsItem)
{
    scene->addItem(graphicsItem);
}


bool is_pathway(const unsigned int& rowIndex, const unsigned int& colIndex)
{
    if (objectMap [rowIndex] [colIndex] != BARRIER) return true;

    return false;
}


bool is_barrier(const unsigned int& rowIndex, const unsigned int& colIndex)
{
    if (objectMap [rowIndex] [colIndex] == BARRIER) return true;

    return false;
}


bool is_within_boundary(const int& rowIndex, const int& colIndex)
{
    if (((rowIndex >= 0) && (rowIndex < MAX_ROWS)) 
    &&  ((colIndex >= 0) && (colIndex < MAX_COLS))) return true;

    return false;
}


Cell_Type get_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex)
{
    return objectMap [rowIndex] [colIndex];
}


void set_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex, Cell_Type cellType)
{
    typedef enum
    {
        CHERRIES   = 0, 
        STRAWBERRY = 1, 
        APPLE      = 2 

    } Fruit_Type;

    if (cellType == BONUS_FRUIT)
    {
        const Fruit_Type fruit = (Fruit_Type) (rand() % 3);

        if (fruit == CHERRIES)
        {
            imageMap[rowIndex][colIndex].setPixmap(QPixmap(":/pics/cherries"));
        }
        else if (fruit == STRAWBERRY)
        {
            imageMap[rowIndex][colIndex].setPixmap(QPixmap(":/pics/strawberry"));
        }
        else /* if (fruit == APPLE) */
        {
            imageMap[rowIndex][colIndex].setPixmap(QPixmap(":/pics/apple"));
        }

        scene->addItem(&(imageMap[rowIndex][colIndex]));
    }

    objectMap [rowIndex] [colIndex] = cellType;
}


void unset_map_cell(const unsigned int& rowIndex, const unsigned int& colIndex)
{
    objectMap [rowIndex] [colIndex] = PATHWAY;

    scene->removeItem(&(imageMap [rowIndex] [colIndex]));
}


void delete_ghost_entity(Ghost *ghostEntity)
{
    bool killedGhostFound = false;

                             killedGhostFound =   inkiesList.removeOne((Inky   *) ghostEntity);
    if ( ! killedGhostFound) killedGhostFound =   clydesList.removeOne((Clyde  *) ghostEntity);
    if ( ! killedGhostFound) killedGhostFound =  pinkiesList.removeOne((Pinky  *) ghostEntity);
    if ( ! killedGhostFound) killedGhostFound = blinkiesList.removeOne((Blinky *) ghostEntity);

    delete ghostEntity;
}


void slot_multiply_ghosts()
{
    const unsigned int numberOf_inkies   =   inkiesList.count();
    const unsigned int numberOf_clydes   =   clydesList.count();
    const unsigned int numberOf_pinkies  =  pinkiesList.count();
    const unsigned int numberOf_blinkies = blinkiesList.count();

    for (unsigned int i = 0; i < numberOf_inkies;   i++)   inkiesList.push_back (new   Inky(vaxman));
    for (unsigned int i = 0; i < numberOf_clydes;   i++)   clydesList.push_back (new  Clyde(vaxman));
    for (unsigned int i = 0; i < numberOf_pinkies;  i++)  pinkiesList.push_back (new  Pinky(vaxman));
    for (unsigned int i = 0; i < numberOf_blinkies; i++) blinkiesList.push_back (new Blinky(vaxman));

    const unsigned int new_totalNumberOf_Ghosts =   inkiesList.count() 
                                                +   clydesList.count() 
                                                +  pinkiesList.count() 
                                                + blinkiesList.count();

    if (new_totalNumberOf_Ghosts >= MAXIMUM_NUMBER_OF_GHOSTS)
    {
        display_termination_message(false);
        delete timer;
        return;
    }
}

