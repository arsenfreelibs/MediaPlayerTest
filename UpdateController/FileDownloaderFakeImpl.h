#ifndef FILEDOWNLOADERFAKEIMPL_H
#define FILEDOWNLOADERFAKEIMPL_H
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"

class FileDownloaderFakeImpl : public FileDownloader
{
    Q_OBJECT

private:
    JobDownloadParams downloadParams_;

public:
    explicit FileDownloaderFakeImpl(QObject *parent = 0);
    
    JobDownloadParams downloadParams() const;
    void setDownloadParams(const JobDownloadParams &downloadParams);

signals:
    
public slots:
    virtual JobID addDownloading(const JobDownloadParams &downloadParams,FileDownloadListener *listener);

    virtual Status removeDownloading(JobID id){}

    virtual Status pauseDownloading(JobID id){}

    virtual Status stopDownloading(JobID id){}
};

#endif // FILEDOWNLOADERFAKEIMPL_H
