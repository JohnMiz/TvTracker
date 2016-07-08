#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbHandler = new DbHandler();
    listOfTvShows = dbHandler->getAllTvShows();


     for(TvSeries ts : listOfTvShows)
     {
        QListWidgetItem* item = new QListWidgetItem(QIcon(QString::fromStdString(ts.image)),QString::fromStdString(std::to_string(ts.id)) + " " + QString::fromStdString(ts.name));
        ui->listWidget->addItem(item);
     }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool exist = false;
    if(ui->itemName->text() != "")
    {
        for(int i = 0; i < ui->listWidget->count(); ++i)
        {
            QListWidgetItem* item = ui->listWidget->item(i);
            if(item->text() == ui->itemName->text())
            {
                QMessageBox::warning(this,"Error","Item is already exist!");
                ui->itemName->setText((""));
                exist=true;
                break;
            }
        }

        // add TvSeries
        if(!exist)
        {
            std::string imagePath = ":/tvshows/got.jpg";

            //add TvSeries to Db

            if(dbHandler->addTvShow(ui->itemName->text().toStdString(),imagePath,std::string("link")))
                qDebug() << "added new tv show!";


            TvSeries end;

            int new_id=1;

            if(listOfTvShows.size()>0)
            {
               end = listOfTvShows.back();
               new_id = end.id+1;
            }

            //add TvSeris to list widget
            QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(imagePath)),QString::fromStdString(std::to_string(new_id)) + " " + ui->itemName->text());
            ui->listWidget->addItem(item);

            // add TvSeries to list of tv series

            listOfTvShows.push_back(TvSeries{new_id,ui->itemName->text().toStdString(),imagePath});

            ui->itemName->setText((""));
        }


    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    std::string itemStr = item->text().toStdString();

    int id = std::stoi(itemStr.substr(0,itemStr.find(" ")));
    std::string name = itemStr.substr(itemStr.find(" ")+1);

    //remove item from db
    dbHandler->deleteTvShow(id,name);

    //remove item from list of TvSeries

    std::list<TvSeries>::iterator end = listOfTvShows.end();
    for(std::list<TvSeries>::iterator it = listOfTvShows.begin();it!=end;)
    {
        if(it->id == id && it->name == name)
            it = listOfTvShows.erase(it);
        else ++it;
    }

    //remove item from list widget
    ui->listWidget->removeItemWidget(item);
}


void MainWindow::on_searchButton_clicked()
{
    if(ui->queryLine->text() != "")
    {
        ui->searchResultsList->clear();
        std::vector<TvSeries> list = manager.searchSeries(ui->queryLine->text().toStdString());
        for(TvSeries ts : list)
        {
            ui->searchResultsList->addItem(new QListWidgetItem(QIcon(":/tvshows/twd.jpg"),QString::fromStdString(ts.name)));
        }
    }
}

void MainWindow::on_searchResultsList_itemDoubleClicked(QListWidgetItem *item)
{
    std::string imagePath = ":/tvshows/got.jpg";

    //add TvSeries to Db

    if(dbHandler->addTvShow(item->text().toStdString(),imagePath,std::string("link")))
        qDebug() << "added new tv show!";


    TvSeries end;

    int new_id=1;

    if(listOfTvShows.size()>0)
    {
       end = listOfTvShows.back();
       new_id = end.id+1;
    }

    //add TvSeris to list widget
    QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(imagePath)),QString::fromStdString(std::to_string(new_id)) + " " + ui->itemName->text());
    ui->listWidget->addItem(item);

    // add TvSeries to list of tv series

    listOfTvShows.push_back(TvSeries{new_id,ui->itemName->text().toStdString(),imagePath});
}
