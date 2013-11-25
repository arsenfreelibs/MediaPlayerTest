#ifndef TORRENTFILEDOWNLOADER_H
#define TORRENTFILEDOWNLOADER_H

#include <QObject>
#include <QTimer>
#include "../../../MediaPlayer/src/Data/PlaylistModelEntry.h"
#include "torrent/ratecontroller.h"
#include "torrent/torrentclient.h"
#include "VLCPlayer.h"


class TorrentFileDownloader : public QObject
{
    Q_OBJECT

protected:
    std::vector<PlaylistModelEntry> entries_;
    VLCPlayer vlcPlayer_;

public:
    explicit TorrentFileDownloader(QObject *parent = 0);

    void downloadAllEntries(std::vector<PlaylistModelEntry> &entries);

    
signals:
    void sendDownloadReportData(QString title, QString status);
    void finishReportCreation();

public slots:


protected slots:
    void onStatusChanged(QString status);
    void onNextDownloading();

private:
    void saveDownloadList(std::vector<PlaylistModelEntry> &entries);
    void startNextDownloading();
    void doDownload(const QString &torrentUrlStr);



    
};

#endif // TORRENTFILEDOWNLOADER_H
