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
         QSqlQuery query;
         if(query.exec("CREATE TABLE IF NOT EXISTS tvshow(id INTEGER PRIMARY KEY, name text, image text);"))
         {
             qDebug() << "tvshow table is opened!";
         }
     }
}

DbHandler::~DbHandler()
{
}

bool DbHandler::addTvShow(std::string& name, std::string& image)
{
    bool success=false;
    QSqlQuery query;
    query.prepare("INSERT INTO tvshow(name, image) VALUES (:name,:image)");
    query.bindValue(":name",QString::fromStdString(name));
     query.bindValue(":image",QString::fromStdString(image));
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addTvShow error:  " << query.lastError();
    }

    return success;
}


 std::list<tvshow> DbHandler::getAllTvShows()
 {
    std::list<tvshow> list;
    QSqlQuery query("SELECT * FROM tvshow");
    int idId = query.record().indexOf("id");
    int idName = query.record().indexOf("name");
    int idImage = query.record().indexOf("image");

    while (query.next())
    {
        int id = query.value(idId).toInt();
       QString name = query.value(idName).toString();
       QString image = query.value(idImage).toString();
       list.push_back(tvshow(id,name.toStdString(),image.toStdString()));
    }

    return list;
 }

 void DbHandler::deleteTvShow(tvshow& ts)
 {
     bool success;
     QSqlQuery query;
     query.prepare("DELETE FROM tvshow WHERE id = (:id) AND name = (:name)");
     query.bindValue(":id",ts.getId());
     query.bindValue(":name", QString::fromStdString(ts.getName()));
     success = query.exec();

     if(!success)
     {
         qDebug() << "removePerson error: "
                  << query.lastError();
     }
 }
