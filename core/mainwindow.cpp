#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbHandler = new DbHandler();
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
            dbHandler->addTvShow((ui->itemName->text().toStdString()));
            ui->listWidget->addItem((ui->itemName->text()));
            ui->itemName->setText((""));
        }
    }
}
