#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>

class FileDownloader : public QObject
{
 Q_OBJECT
 public:
  explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);
  virtual ~FileDownloader();


  QByteArray getDownloadedData() const;

private slots:
    void replyFinished(QNetworkReply *reply);
private:

  QNetworkAccessManager* netManager;
  QByteArray downloadedData;
};

#endif // FILEDOWNLOADER_H
