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
        QListWidgetItem* item = new QListWidgetItem();
        ui->listWidget->addItem(item);
        auto wid = new CustomListItem(this,ts,1);
        item->setSizeHint(QSize(wid->width(),44));
        ui->listWidget->setItemWidget(item,wid);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    /*
     auto widget =  (CustomListItem*)ui->listWidget->itemWidget(item);

    //remove item from db
    dbHandler->deleteTvShow(widget->getTvSeries().id,widget->getTvSeries().name);

    //remove item from list of TvSeries

    std::list<TvSeries>::iterator end = listOfTvShows.end();
    for(std::list<TvSeries>::iterator it = listOfTvShows.begin();it!=end;)
    {
        if(it->id == widget->getTvSeries().id && it->name == widget->getTvSeries().name)
            it = listOfTvShows.erase(it);
        else ++it;
    }


    //remove item from list widget
    ui->listWidget->removeItemWidget(item);
    */
}


void MainWindow::on_searchButton_clicked()
{
    if(ui->queryLine->text() != "")
    {
        ui->searchResultsList->clear();
        std::vector<TvSeries> list = manager.searchSeries(ui->queryLine->text().toStdString());
        for(TvSeries ts : list)
        {
            QListWidgetItem* item = new QListWidgetItem();
            ui->searchResultsList->addItem(item);
            ts.image = ":/images/got.jpg";
            auto wid = new CustomListItem(this,ts,0);
            item->setSizeHint(QSize(wid->width(),44));
            ui->searchResultsList->setItemWidget(item,wid);
        }
    }
}

void MainWindow::on_searchResultsList_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "are you sure", "Do you want to add this to the list?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        auto widget = (CustomListItem*)ui->searchResultsList->itemWidget(item);
        bool exist = false;

        for(int i = 0; i < ui->listWidget->count(); ++i)
        {
            QListWidgetItem* item = ui->listWidget->item(i);
            auto tvitem = (CustomListItem*)ui->listWidget->itemWidget(item);
            if(tvitem->getTvSeries().name == widget->getTvSeries().name)
            {
              QMessageBox::critical(this,"Error","Item is already exist!");
              exist=true;
              break;
            }
        }

        // add TvSeries
        if(!exist)
        {
         //add TvSeries to Db

          if(dbHandler->addTvShow(widget->getTvSeries().name,widget->getTvSeries().image,widget->getTvSeries().link))
               qDebug() << "added new tv show!";


           TvSeries end;

           int new_id=1;

           if(listOfTvShows.size()>0)
           {
                end = listOfTvShows.back();
                new_id = end.id+1;
           }

           //add TvSeris to list widget

           QListWidgetItem *item = new QListWidgetItem();
           ui->searchResultsList->removeItemWidget(item);
           ui->listWidget->addItem(item);
           item->setSizeHint(QSize(widget->width(),44));
           widget->setType(1);
           ui->listWidget->setItemWidget(item,widget);

           // add TvSeries to list of tv series

           listOfTvShows.push_back(TvSeries{new_id,widget->getTvSeries().name,widget->getTvSeries().image,widget->getTvSeries().link});
        }
   }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "are you sure", "Do you want to get information about this series?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        auto tvitem = (CustomListItem*)ui->listWidget->itemWidget(item);
        int numberOfSeasons = manager.getNumberOfSeasons(tvitem->getTvSeries().link);

        Season lastSeason = manager.getSeasonEpisodes(tvitem->getTvSeries().link,numberOfSeasons);
        for(Episode ep : lastSeason.episodes)
        {
            qDebug() << "Number: " << ep.number << " AirDate: " << QString::fromStdString(ep.date);
        }
    }
}
