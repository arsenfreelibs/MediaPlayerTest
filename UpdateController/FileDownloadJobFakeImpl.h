#ifndef FILEDOWNLOADJOBFAKEIMPL_H
#define FILEDOWNLOADJOBFAKEIMPL_H

#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"

class FileDownloadJobFakeImpl : public FileDownloadJob
{
    Q_OBJECT

public:
    explicit FileDownloadJobFakeImpl(QObject *parent = 0);
    
    virtual void setUrl(const QString &url);
    virtual QString url() const;
    virtual void setTorrentUrl(const QString &torrentUrl);
    virtual QString torrentUrl() const;
    virtual void setDestinationFolder(const QString &directory);
    virtual QString destinationFolder() const;
    virtual void setFileName(const QString &directory);
    virtual QString fileName() const;

    // State and error.
    virtual State state() const;
    virtual QString stateString() const;
    virtual Error error() const;
    virtual QString errorString() const;

signals:
    
public slots:
    virtual void start();
    virtual void stop();
    virtual void setPaused(bool paused);
    
};

#endif // FILEDOWNLOADJOBFAKEIMPL_H
