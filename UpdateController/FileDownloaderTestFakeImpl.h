#ifndef FILEDOWNLOADERTESTFAKEIMPL_H
#define FILEDOWNLOADERTESTFAKEIMPL_H
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.h"

class FileDownloaderTestFakeImpl : public FileDownloaderImpl
{
    Q_OBJECT
public:
    explicit FileDownloaderTestFakeImpl(QObject *parent = 0);
    
    int jobCount();
signals:
    
public slots:
    
protected:

};

#endif // FILEDOWNLOADERTESTFAKEIMPL_H
