#include "sourcegrabber.h"

std::string SourceGrabber::grabSearchIMDB(const std::string&  title)
{
    QString url = QString::fromStdString(std::string("http://www.imdb.com/find?q=" + title + "&s=tt&ttype=tv&ref_=fn_tv"));
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll(); // Source should be stored here

    return html.toStdString();
}

std::string SourceGrabber::grabURL(const std::string& url)
{
     return std::string();
}

