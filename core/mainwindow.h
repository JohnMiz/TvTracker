#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <string>
#include "dbhandler.h"
#include <memory>
#include <list>
#include <QListWidget>
#include "tvshow.h"
#include <QWidgetList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DbHandler* dbHandler;
    std::list<tvshow> listOfTvShows;
};

#endif // MAINWINDOW_H
