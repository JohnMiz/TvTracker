#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QObject *parent) : QObject(parent)
{
     netManager = new QNetworkAccessManager(this);
     connect(netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
     QNetworkRequest request(imageUrl);

     netManager->get(request);
}

FileDownloader::~FileDownloader()
{

}

void FileDownloader::replyFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
     {
         qDebug() << "Error: " <<  reply->errorString();
     }
     else
     {
         downloadedData = reply->readAll();

     }
}

QByteArray FileDownloader::getDownloadedData() const
{
    return downloadedData;
}
