#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QWidgetList>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>

#include "db/dbhandler.h"
#include "tvtrackermanager.h"
#include "http/filedownloader.h"
#include "customlistitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int calculateTimeLeftToDate(const Date& date);

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_searchButton_clicked();
    void on_searchResultsList_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DbHandler* dbHandler;
    std::list<TvSeries> listOfTvShows;
    TvTrackerManager manager;
};

#endif // MAINWINDOW_H
