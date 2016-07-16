#ifndef CUSTOMLISTITEM_H
#define CUSTOMLISTITEM_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QMessageBox>

#include "http/sourcegrabber.h"
#include "db/dbhandler.h"

struct imageObject
{
    QImage img;
    QPoint pos;
};

class CustomListItem : public QWidget
{
    Q_OBJECT
public:
     CustomListItem(QWidget *parent, TvSeries tv, int type);
     TvSeries& getTvSeries();
     QPushButton*& getButton();

     int getType() const;
     void setType(int value);

public slots:
     void handleClick(bool);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int type;
    TvSeries ts;
    DbHandler* dbHandler;
};

#endif
