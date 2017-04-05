#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myNewGraph.hpp"
#include "PathBFS.hpp"
#include "PathDFS.hpp"
#include <QList>
#include <QRect>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QThread>
#include <QMessageBox>
#include <vector>
#include <QTimer>

#define AllowOblique false

typedef PathBFS FSType; //Type of pathfinding algorithm

const int RECT_SIZE = 70;

int currentFrom = 0; // To record current From and To point
int currentTo = 0;

FSType* bfs = NULL; //Pathfinding class
std::vector<int> vec;// To record the result of the algorithm

QTimer* timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),graph(myNewGraph(100))
{
    ui->setupUi(this);
    this->setMaximumSize(this->size());
    for(int y = 0; y< 10; y ++)
    {
        for(int x = 0; x < 10; x++)
        {
            rects.append(new MyRect(QRect(x*70,y*70,RECT_SIZE,RECT_SIZE)));//Initialize the rects(nodes)
        }
    }
    timer = new QTimer();
    timer->setInterval(500);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTimerEvent()));
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QBrush originalBrush = p.brush();
    for(int i =0; i<rects.size();i++)
    {
        p.setPen(QPen(QColor(0,0,0),5));
        p.drawRect(rects.at(i)->Rect);

        if(rects.at(i)->isClicked)
        {
            p.setBrush(QBrush(QColor(137,207,240)));
        }
        else if(rects.at(i)->isFromPos)
        {
            p.setBrush(QBrush(QColor(137,255,240)));
        }
        else if(rects.at(i)->isToPos)
        {
            p.setBrush(QBrush(QColor(100,170,255)));
        }
        else if(rects.at(i)->isPartOfWay)
        {
            p.setBrush(QBrush(QColor(255,255,170)));
        }
        p.drawRect(rects.at(i)->Rect);
        p.setBrush(originalBrush);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    static bool isForFrom = true;
    switch(currentStatus)
    {
        case Editing:
        for(int i = 0; i < rects.size();i++)
        {
            QRect temp = rects.at(i)->Rect;
            if(e->x()>temp.x()
                    &&e->x()<temp.x()+temp.width()
                    &&e->y()>temp.y()
                    &&e->y()<temp.y()+temp.height())//Mouse position check
            {
                rects.at(i)->isClicked = !rects.at(i)->isClicked;
                break;
            }
        }
        break;
    case Setting:
        for(int i = 0; i < rects.size();i++)//Set the start and end point
        {
            if(rects.at(i)->isClicked)
            {
                continue;
            }
            QRect temp = rects.at(i)->Rect;
            if(e->x()>temp.x()
                    &&e->x()<temp.x()+temp.width()
                    &&e->y()>temp.y()
                    &&e->y()<temp.y()+temp.height())
            {
                if(isForFrom)
                {
                    rects.at(currentFrom)->isFromPos = false;
                    rects.at(i)->isFromPos = true;
                    currentFrom = i;
                    isForFrom = false;
                    break;
                }
                else
                {
                    rects.at(currentTo)->isToPos = false;
                    rects.at(i)->isToPos = true;
                    currentTo = i;
                    isForFrom = true;
                    break;
                }
            }
        }
        break;
    case Playing:

        break;
    default:break;
    }
    this->update();
}

void MainWindow::on_BtnConfirm_clicked()//Confirm the map
{
    currentStatus = ::Setting;
    ui->BtnConfirm->setEnabled(false);
    ui->BtnPosConfirm->setEnabled(true);
    QMessageBox::information(this,"Confirm","The map is locked");

    for(int y = 0; y< 10; y ++)//Add edges for every node
    {
        for(int x = 0; x < 10; x++)
        {
            const int currentPos = y*10 + x;
            if(rects.at(currentPos)->isClicked)
            {
                continue;
            }
            if(y>=1 && !rects.at(currentPos-10)->isClicked)
            {
                graph.addEdge(currentPos,currentPos-10);
            }
#if AllowOblique
            if(y>=1 && x<9 && !rects.at(currentPos-9)->isClicked)
            {
                graph.addEdge(currentPos,currentPos-9);
            }
#endif
            if(x<9 && !rects.at(currentPos+1)->isClicked)
            {
                graph.addEdge(currentPos,currentPos+1);
            }
#if AllowOblique
            if(x<9 && y<9 && !rects.at(currentPos+11)->isClicked)
            {
                graph.addEdge(currentPos,currentPos+11);
            }
#endif
            if(y<9 && !rects.at(currentPos+10)->isClicked)
            {
                graph.addEdge(currentPos,currentPos+10);
            }
#if AllowOblique
            if(y<9 && x >=1 && !rects.at(currentPos+9)->isClicked)
            {
                graph.addEdge(currentPos,currentPos+9);
            }
#endif
            if(x>=1 && !rects.at(currentPos-1)->isClicked)
            {
                graph.addEdge(currentPos,currentPos-1);
            }
#if AllowOblique
            if(x>=1 && y>=1 && !rects.at(currentPos-11)->isClicked)
            {
                graph.addEdge(currentPos,currentPos-11);
            }
#endif
        }
    }
    QMessageBox::information(this,"Process Complete","The map have been successfully processed！");
}

void MainWindow::on_BtnAction_clicked()
{
    ui->BtnAction->setEnabled(false);
    if(vec.size()==0)
    {
        QMessageBox::information(this,"No Way!","No way! Don't waste your time！");
        return;
    }
    timer->start();
}

void MainWindow::on_BtnPosConfirm_clicked()
{
    if(currentFrom == currentTo)
    {
        QMessageBox::information(this,"Error","Start and end point must not be the same or empty.");
        return;
    }
    currentStatus = ::Playing;
    ui->BtnPosConfirm->setEnabled(false);
    ui->BtnAction->setEnabled(true);
    delete bfs;
    bfs = new FSType(graph,currentFrom);
    bfs->findPath(currentTo,vec);
    QMessageBox::information(this,"Confirm","Ready for action！");
}
void MainWindow::myTimerEvent()
{
    static int index = 0;
    if(index >= (int)vec.size()-1)
    {
        QMessageBox::information(this,"Status Report！","I successfully get the destination！");
        timer->stop();
    }
    rects.at(vec.at(index++))->isPartOfWay = true;
    this->update();
}
