#include "TorrentFileDownloader.h"

TorrentFileDownloader::TorrentFileDownloader(QObject *parent) :
    QObject(parent)
{
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
        doDownload(entries_.back().torrentUrl());
    }else{
        emit finishReportCreation();
    }
}

void TorrentFileDownloader::doDownload(const QString &torrentUrlStr)
{
    TorrentClient *client = new TorrentClient(this);
    if (!client->setTorrent(torrentUrlStr)) {
        return; //TODO add emit signal with bad report data
    }
}
