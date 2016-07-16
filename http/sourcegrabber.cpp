#include "sourcegrabber.h"

SourceGrabber::SourceGrabber()
{
}

std::string SourceGrabber::grabSearchIMDB(const std::string&  title)
{
    std::string url = std::string("http://www.imdb.com/find?q=" + title + "&s=tt&ttype=tv&ref_=fn_tv");
    return getSourceCode(url);
}

std::string SourceGrabber::grabURL(const std::string& url)
{
    return getSourceCode(url);
}

std::string SourceGrabber::getSourceCode(const std::string &url)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(QString::fromStdString(url))));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll(); // Source should be stored here

    return html.toStdString();
}

