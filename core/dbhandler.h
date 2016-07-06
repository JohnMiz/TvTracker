#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <list>
#include "sourcegrabber.h"

class DbHandler
{
public:
    DbHandler();
    ~DbHandler();

    bool addTvShow(std::string& name, std::string &image,std::string& link);
    std::list<TvSeries> getAllTvShows();

    void deleteTvShow(int &id, std::string name);

private:
   QSqlDatabase db;

};

#endif // DBHANDLER_H
