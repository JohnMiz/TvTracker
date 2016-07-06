#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QWidgetList>

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <chrono>

#include "dbhandler.h"
#include "tvtrackermanager.h"

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
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    DbHandler* dbHandler;
    std::list<TvSeries> listOfTvShows;
    TvTrackerManager manager;
};

#endif // MAINWINDOW_H
