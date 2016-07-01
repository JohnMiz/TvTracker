#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbHandler = new DbHandler();
    listOfTvShows = dbHandler->getAllTvShows();


     for(tvshow ts : listOfTvShows)
       {
           QListWidgetItem* item = new QListWidgetItem(QIcon(QString::fromStdString(ts.getImage())),QString::fromStdString(std::to_string(ts.getId())) + " "+ QString::fromStdString(ts.getName()));
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
        if(!exist)
        {
            std::string imagePath = ":/tvshows/silicon_valley.jpg";
            if(dbHandler->addTvShow(ui->itemName->text().toStdString(),imagePath))
                qDebug() << "added new tv show!";

            if(listOfTvShows.size()==0)
            {
                QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(imagePath)),QString::fromStdString(std::to_string(1))+" "+ui->itemName->text());
                ui->listWidget->addItem(item);

                listOfTvShows.push_back(tvshow(1,ui->itemName->text().toStdString(),imagePath));

            }
            else{
            tvshow end = listOfTvShows.back();
            QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(imagePath)),QString::fromStdString(std::to_string(end.getId()+1))+" "+ui->itemName->text());
            ui->listWidget->addItem(item);

            listOfTvShows.push_back(tvshow(end.getId()+1,ui->itemName->text().toStdString(),imagePath));
            }
            ui->itemName->setText((""));
        }


    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->listWidget->removeItemWidget(item);
    std::string itemStr = item->text().toStdString();
    dbHandler->deleteTvShow(tvshow(std::stoi(itemStr.substr(0,itemStr.find(" "))),itemStr.substr(itemStr.find(" ")+1)));
    std::list<tvshow>::iterator end = listOfTvShows.end();
    for(std::list<tvshow>::iterator it = listOfTvShows.begin();
        it!=end;
        )
    {
        if(it->getId() == std::stoi(itemStr.substr(0,itemStr.find(" "))) && it->getName() ==itemStr.substr(itemStr.find(" ")+1) )
            it = listOfTvShows.erase(it);
        else ++it;
    }


}
