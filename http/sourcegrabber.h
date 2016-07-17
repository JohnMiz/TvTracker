#ifndef SOURCEGRABBER_H
#define SOURCEGRABBER_H

#include <string>
#include <iostream>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QString>
#include <QDebug>
#include <fstream>
#include <vector>

struct Date
{
    int day;
    int month;
    int year;
};

struct TvSeries {
    int id;
    std::string name;
    std::string image;
    std::string link;
};

struct Episode
{
    int number;
    Date airDate;
};

struct Season
{
    int number;
    std::vector<Episode> episodes;
};

class SourceGrabber {
public:
     SourceGrabber();
     SourceGrabber(const std::string& title);

     std::string grabSearchIMDB(const std::string& title);
     std::string grabURL(const std::string& url);
     std::string getSourceCode(const std::string &url);

};

#endif // SOURCEGRABBER_H
