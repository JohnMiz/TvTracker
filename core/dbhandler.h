#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <list>
#include "tvshow.h"

class DbHandler
{
public:
    DbHandler();
    ~DbHandler();

    bool addTvShow(std::string& name, std::string &image);
    std::list<tvshow> getAllTvShows();

    void deleteTvShow(tvshow &ts);

private:
   QSqlDatabase db;

};

#endif // DBHANDLER_H
