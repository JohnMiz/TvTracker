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

#include "db/dbhandler.h"
#include "tvtrackermanager.h"
#include "http/filedownloader.h"

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

    void on_searchResultsList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DbHandler* dbHandler;
    std::list<TvSeries> listOfTvShows;
    TvTrackerManager manager;
};

#endif // MAINWINDOW_H
