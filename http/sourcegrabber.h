#ifndef SOURCEGRABBER_H
#define SOURCEGRABBER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QString>
#include <QDebug>

#include <core/tvtrackertypes.h>

class SourceGrabber {
public:
     SourceGrabber();
     SourceGrabber(const std::string& title);

     std::string grabSearchIMDB(const std::string& title);
     std::string grabURL(const std::string& url);
     std::string getSourceCode(const std::string &url);

};

#endif // SOURCEGRABBER_H
