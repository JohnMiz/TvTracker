#include "customlistitem.h"

CustomListItem::CustomListItem(QWidget *parent, TvSeries tv,int type) : QWidget(parent),ts(tv),type(type)
{
    dbHandler = new DbHandler();
    if(type == 1)
    {
        QPushButton * button = new QPushButton("",this);

        button->setMaximumWidth(20);
        button->setMaximumHeight(20);
        button->setIcon(QIcon(":/images/Black_Remove.png"));

        QObject::connect(button,SIGNAL(clicked(bool)),this,SLOT(handleClick(bool)));

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(button);

        button->move(385, 0);
        button->show();
    }
}

TvSeries &CustomListItem::getTvSeries()
{
    return ts;
}

void CustomListItem::handleClick(bool)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "are you sure", "Do you want to delete this tv series?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        dbHandler->deleteTvShow(ts.id,ts.name);
    }
}

void CustomListItem::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    imageObject io{QImage(QString::fromStdString(ts.image)),QPoint(0,0)};

    p.drawImage(io.pos,io.img);
    QString str = QString::fromStdString(ts.name+ " " + ts.link);
    p.setFont(QFont("arial",10));
    p.drawText(io.pos.x() + 50,io.pos.y() + 25,str);
}
