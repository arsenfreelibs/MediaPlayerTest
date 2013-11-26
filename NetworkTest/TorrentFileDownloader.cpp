#include "TorrentFileDownloader.h"

TorrentFileDownloader::TorrentFileDownloader(QObject *parent) :
    QObject(parent)
{
    QObject::connect(&vlcPlayer_, SIGNAL(statusChanged(QString)),
                     this, SLOT(onStatusChanged(QString)));
}

void TorrentFileDownloader::downloadAllEntries(std::vector<PlaylistModelEntry> &entries)
{
    saveDownloadList(entries);
    startNextDownloading();
}

void TorrentFileDownloader::saveDownloadList(std::vector<PlaylistModelEntry> &entries)
{
    entries_= entries;
}

void TorrentFileDownloader::startNextDownloading()
{
    if(entries_.size()>0){
        QTimer::singleShot((testingTime_+1)*1000, this, SLOT(onStopDownloading()));
        qDebug().nospace() << entries_.back().title();
        doDownload(entries_.back().torrentUrl());
    }else{
        emit finishReportCreation();
    }
}

void TorrentFileDownloader::doDownload(const QString &torrentUrlStr)
{
    statusOfCurentDownloading_ = NO_STATUS;
    vlcPlayer_.playTorrentURL(torrentUrlStr);
}

void TorrentFileDownloader::onStatusChanged(QString status)
{
    if(status.length()>3){
        statusOfCurentDownloading_=status;
    }
}

void TorrentFileDownloader::onNextDownloading()
{
    entries_.pop_back();
    startNextDownloading();
}

void TorrentFileDownloader::onStopDownloading()
{
    qDebug().nospace() <<statusOfCurentDownloading_.toUtf8();
    emit sendDownloadReportData(statusOfCurentDownloading_);
    onNextDownloading();
}

int TorrentFileDownloader::testingTime() const
{
    return testingTime_;
}

void TorrentFileDownloader::setTestingTime(int testingTime)
{
    testingTime_ = testingTime;
}
