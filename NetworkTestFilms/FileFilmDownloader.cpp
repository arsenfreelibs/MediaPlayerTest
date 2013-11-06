#include "FileFilmDownloader.h"

FileFilmDownloader::FileFilmDownloader(QObject *parent) :
    QObject(parent),reply_(NULL)
{
    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            SLOT(onFinished(QNetworkReply*)));
}

void FileFilmDownloader::downloadAllEntries(std::vector<PlaylistModelEntry> &entries)
{
    saveDownloadList(entries);
    startNextDownloading();
}

void FileFilmDownloader::saveDownloadList(std::vector<PlaylistModelEntry> &entries)
{
    entries_= entries;
}

void FileFilmDownloader::startNextDownloading()
{
    if(entries_.size()>0){
        doDownload(entries_.back().url());
    }else{
        emit finishReportCreation();
    }
}

void FileFilmDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    //    qDebug().nospace() << "bytesReceived = " << bytesReceived << "bytesTotal = " <<bytesTotal;
    trias_++;
    if(trias_>testing_trias_+TRIAS_AMOUNT){
        stopDownloading();
    }
}

void FileFilmDownloader::stopDownloading()
{
    if(reply_->isRunning()){
        reply_->abort();
    }
}

void FileFilmDownloader::onFinished(QNetworkReply *reply)
{
    sendReportData();
    startNextDownloading();
}

void FileFilmDownloader::sendReportData()
{
    QString status = TEST_NOT_PASS_STR;
    QString title = entries_.back().title();
    if(trias_ > testing_trias_){
        status = TEST_PASS_STR;
    }
    entries_.pop_back();

    emit sendDownloadReportData(title, status);
}

void FileFilmDownloader::doDownload(const QString &urlStr)
{
    performGetRequest(createRequest(urlStr));
}

QNetworkRequest FileFilmDownloader::createRequest(const QString &urlStr)
{
    QUrl url(urlStr);
    QNetworkRequest request(url);
    return request;
}

void FileFilmDownloader::performGetRequest(QNetworkRequest request)
{
    finishPrevDownloading();
    takeNewReply(request);
}
void FileFilmDownloader::finishPrevDownloading()
{
    if(reply_){
        stopDownloading();
        reply_->deleteLater();
    }
}

void FileFilmDownloader::takeNewReply(QNetworkRequest request)
{
    reply_ = manager_.get(request);
    trias_ = 0;
    QObject::connect(reply_, SIGNAL(downloadProgress(qint64, qint64)),
                     this, SLOT(onDownloadProgress(qint64 , qint64 )));
}

int FileFilmDownloader::testing_time() const
{
    return testing_trias_;
}

void FileFilmDownloader::setTesting_time(int testing_time)
{
    testing_trias_ = testing_time;
}
