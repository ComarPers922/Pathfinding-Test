#ifndef MYRECT_H
#define MYRECT_H
#include <QRect>

class MyRect
{
public:
    QRect Rect;
    bool isClicked = false;
    bool isFromPos = false;
    bool isToPos = false;
    bool isPartOfWay = false;

    MyRect(QRect rect);
};

#endif // MYRECT_H
