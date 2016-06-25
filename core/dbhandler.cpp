#include "dbhandler.h"

DbHandler::DbHandler()
{
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("tvdb.db");

     if(!db.open())
     {
         QMessageBox::critical(0, "Database Error", db.lastError().text());
     }
     else{
         if(query.exec("CREATE TABLE IF NOT EXISTS tvshow(id INTEGER PRIMARY KEY, name text);"))
         {
             qDebug() << "tvshow table is created!";
         }
     }
}

DbHandler::~DbHandler()
{
}

bool DbHandler::addTvShow(std::string &name)
{
    bool success=false;
    query.prepare("INSERT INTO tvshow(name) VALUES (:name)");
    query.bindValue(":name",QString::fromStdString(name));

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addTvShow error:  "
                  << query.lastError();
    }

    return success;
}
