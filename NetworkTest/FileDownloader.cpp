#include "FileDownloader.h"

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent),reply_(NULL)
{
    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            SLOT(onFinished(QNetworkReply*)));
}

void FileDownloader::downloadAllEntries(std::vector<PlaylistModelEntry> &entries)
{
    saveDownloadList(entries);
    startNextDownloading();
}

void FileDownloader::saveDownloadList(std::vector<PlaylistModelEntry> &entries)
{
    entries_= entries;
}

void FileDownloader::startNextDownloading()
{
    if(entries_.size()>0){
        doDownload(entries_.back().url());
    }
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
//    qDebug().nospace() << "bytesReceived = " << bytesReceived << "bytesTotal = " <<bytesTotal;
    trias_++;
    if(trias_>TRIAS_AMOUNT){
        stopDownloading();
    }
}

void FileDownloader::stopDownloading()
{
    if(reply_->isRunning()){
        reply_->abort();
    }
}

void FileDownloader::onFinished(QNetworkReply *reply)
{
    qDebug().nospace() << "title = " << entries_.back().title() << "  status = " << trias_;
    entries_.pop_back();
    startNextDownloading();
}

void FileDownloader::doDownload(const QString &urlStr)
{
    QUrl url(urlStr);
//    QUrl url("urlStr");
    QNetworkRequest request(url);
    getRequest(request);
}

void FileDownloader::getRequest(QNetworkRequest request)
{
    finishPreDownloading();
    takeNewReply(request);
}
void FileDownloader::finishPreDownloading()
{
    if(reply_){
        stopDownloading();
        reply_->deleteLater();
    }
}

void FileDownloader::takeNewReply(QNetworkRequest request)
{
    reply_ = manager_.get(request);
    trias_ = 0;
    QObject::connect(reply_, SIGNAL(downloadProgress(qint64, qint64)),
                     this, SLOT(onDownloadProgress(qint64 , qint64 )));
}
