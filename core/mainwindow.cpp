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

int MainWindow::calculateTimeLeftToDate(const Date &date)
{
    time_t t = time(0);

    struct std::tm currentTime = *localtime(&t);
    currentTime.tm_hour = 0;
    currentTime.tm_min = 0;
    currentTime.tm_sec = 0;

    struct std::tm airDate;
    airDate.tm_hour = 0;
    airDate.tm_min = 0;
    airDate.tm_sec = 0;
    airDate.tm_mday = date.day;
    airDate.tm_mon = date.month == 0 ? 0 : date.month - 1 ;
    airDate.tm_year = date.year - 1900;

    std::time_t currentTime_time = std::mktime(&currentTime);
    std::time_t airDate_time = std::mktime(&airDate);

    return std::difftime(airDate_time, currentTime_time) / (60 * 60 * 24);
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
            FileDownloader* f = new FileDownloader(QString::fromStdString(ts.image),this);
            std::string path = "C:\\Users\\Sabri_000\\Documents\\TvTracker\\Resources\\images\\" + ts.name + ".jpg";

            std::ofstream file(path);
            file << f->getDownloadedData().toStdString();
            file.close();

            ts.image = path;
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
        bool found = false;

        Episode currentEp{0,0};
        int season=0;

        //Finding the current episode

        for(int i = 1; i <= numberOfSeasons && !found; ++i)
        {
            Season s = manager.getSeasonEpisodes(tvitem->getTvSeries().link,i);
            for(Episode ep : s.episodes)
            {
                if(calculateTimeLeftToDate(ep.airDate) > 0)
                {
                    currentEp = ep;
                    season = s.number;
                    found = true;
                    break;
                }
            }
        }

        if(currentEp.number == 0 && currentEp.airDate.day==0 && currentEp.airDate.month==0 && currentEp.airDate.year==0)
        {
            QMessageBox::critical(this,"Error","Did not get current episode!");
        }
        else
        {
            qDebug() << "Season:" << season << "Episode:" << currentEp.number;
            qDebug() << "AirDate:" << currentEp.airDate.day << "." << currentEp.airDate.month << "." << currentEp.airDate.year;
        }
    }
}
