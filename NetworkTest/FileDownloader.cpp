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
    }else{
        emit finishReportCreation();
    }
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    //    qDebug().nospace() << "bytesReceived = " << bytesReceived << "bytesTotal = " <<bytesTotal;
    trias_++;
    if(trias_>testing_trias_+TRIAS_AMOUNT){
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
    sendReportData();
    startNextDownloading();
}

void FileDownloader::sendReportData()
{
    QString status = TEST_NOT_PASS_STR;
    QString title = entries_.back().title();
    if(trias_ > testing_trias_){
        status = TEST_PASS_STR;
    }
    entries_.pop_back();
    
    emit sendDownloadReportData(title, status);
}

void FileDownloader::doDownload(const QString &urlStr)
{
    performGetRequest(createRequest(urlStr));
}

QNetworkRequest FileDownloader::createRequest(const QString &urlStr)
{
    QUrl url(urlStr);
    QNetworkRequest request(url);
    return request;
}

void FileDownloader::performGetRequest(QNetworkRequest request)
{
    finishPrevDownloading();
    takeNewReply(request);
}
void FileDownloader::finishPrevDownloading()
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

int FileDownloader::testing_time() const
{
    return testing_trias_;
}

void FileDownloader::setTesting_time(int testing_time)
{
    testing_trias_ = testing_time;
}
