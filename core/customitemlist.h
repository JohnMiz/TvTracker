#ifndef CUSTOMITEMLIST_H
#define CUSTOMITEMLIST_H

#include <QWidget>
#include <QPainter>

class CustomItemList : public QWidget
{
    Q_OBJECT
public:
    explicit CustomItemList(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMITEMLIST_H
