#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrect.h"
#include "myNewGraph.hpp"

namespace Ui
{
class MainWindow;
}
enum Status
{
    Editing,Setting,Playing
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BtnConfirm_clicked();

    void on_BtnAction_clicked();

    void on_BtnPosConfirm_clicked();

private:
    Status currentStatus = ::Editing;
    Ui::MainWindow *ui;
    myNewGraph graph;
    QList<MyRect*> rects;
    virtual void paintEvent(QPaintEvent*);
    virtual void mousePressEvent(QMouseEvent* e);
private slots:
    void myTimerEvent();
};

#endif // MAINWINDOW_H
