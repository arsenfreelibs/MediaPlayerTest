#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "../../../MediaPlayer/src/Data/PlaylistModelEntry.h"


#define TRIAS_AMOUNT 10

class FileDownloader : public QObject
{
    Q_OBJECT

protected:
    QNetworkAccessManager manager_;
    QNetworkReply *reply_;
    int trias_;
    std::vector<PlaylistModelEntry> entries_;

public:
    explicit FileDownloader(QObject *parent = 0);

    void downloadAllEntries(std::vector<PlaylistModelEntry> &entries);
    void doDownload(const QString &urlStr);

signals:
    
public slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onFinished(QNetworkReply *reply);

private:
    void getRequest(QNetworkRequest request);
    void stopDownloading();
    void finishPreDownloading();
    void takeNewReply(QNetworkRequest request);
    void saveDownloadList(std::vector<PlaylistModelEntry> &entries);
    void startNextDownloading();
    
};

#endif // FILEDOWNLOADER_H
