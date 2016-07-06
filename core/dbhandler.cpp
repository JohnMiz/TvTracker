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
         if(query.exec("CREATE TABLE IF NOT EXISTS tvshow(id INTEGER PRIMARY KEY, name text, image text,link text);"))
         {
             qDebug() << "tvshow table is opened!";
         }
     }
}

DbHandler::~DbHandler()
{
}

bool DbHandler::addTvShow(std::string& name, std::string& image, std::string &link)
{
    bool success=false;
    QSqlQuery query;
    query.prepare("INSERT INTO tvshow(name, image, link) VALUES (:name,:image,:link)");
    query.bindValue(":name",QString::fromStdString(name));
    query.bindValue(":image",QString::fromStdString(image));
    query.bindValue(":link",QString::fromStdString(link));
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


 std::list<TvSeries> DbHandler::getAllTvShows()
 {
    std::list<TvSeries> list;
    QSqlQuery query("SELECT * FROM tvshow");
    int idId = query.record().indexOf("id");
    int idName = query.record().indexOf("name");
    int idImage = query.record().indexOf("image");
    int idLink = query.record().indexOf("link");

    while (query.next())
    {
        int id = query.value(idId).toInt();
       QString name = query.value(idName).toString();
       QString image = query.value(idImage).toString();
       QString link = query.value(idLink).toString();
       list.push_back(TvSeries{id,name.toStdString(),image.toStdString(),link.toStdString()});
    }

    return list;
 }

 void DbHandler::deleteTvShow(int& id, std::string name)
 {
     bool success;
     QSqlQuery query;
     query.prepare("DELETE FROM tvshow WHERE id = (:id) AND name = (:name)");
     query.bindValue(":id",id);
     query.bindValue(":name", QString::fromStdString(name));
     success = query.exec();

     if(!success)
     {
         qDebug() << "removePerson error: "
                  << query.lastError();
     }
 }
