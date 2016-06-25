#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <iostream>

class DbHandler
{
public:
    DbHandler();
    ~DbHandler();

    bool addTvShow(std::string& name);

private:
   QSqlDatabase db;
   QSqlQuery query;
};

#endif // DBHANDLER_H
