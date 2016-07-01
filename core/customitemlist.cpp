#include "customitemlist.h"

CustomItemList::CustomItemList(QWidget *parent) : QWidget(parent)
{

}

void CustomItemList::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(100,100,QImage(":/tvshows/girls.jpg"));
}
