#ifndef FILEFILMDOWNLOADER_H
#define FILEFILMDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "../../../MediaPlayer/src/Data/PlaylistModelEntry.h"

#define TRIAS_AMOUNT 2
#define TEST_PASS_STR "да"
#define TEST_NOT_PASS_STR "нет"

class FileFilmDownloader : public QObject
{
    Q_OBJECT

protected:
    QNetworkAccessManager manager_;
    QNetworkReply *reply_;

    int trias_;
    int testing_trias_;

    std::vector<PlaylistModelEntry> entries_;

public:
    explicit FileFilmDownloader(QObject *parent = 0);

    void downloadAllEntries(std::vector<PlaylistModelEntry> &entries);
    void doDownload(const QString &urlStr);

    QNetworkRequest createRequest(const QString &urlStr);
    int testing_time() const;
    void setTesting_time(int testing_time);

signals:
    void sendDownloadReportData(QString title, QString status);
    void finishReportCreation();

public slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onFinished(QNetworkReply *reply);

private:
    void performGetRequest(QNetworkRequest request);
    void stopDownloading();
    void finishPrevDownloading();
    void takeNewReply(QNetworkRequest request);
    void saveDownloadList(std::vector<PlaylistModelEntry> &entries);
    void startNextDownloading();
    void sendReportData();

};

#endif // FILEFILMDOWNLOADER_H
