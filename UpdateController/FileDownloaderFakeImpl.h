#ifndef FILEDOWNLOADERFAKEIMPL_H
#define FILEDOWNLOADERFAKEIMPL_H
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"

class FileDownloaderFakeImpl : public FileDownloader
{
    Q_OBJECT
public:
    explicit FileDownloaderFakeImpl(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // FILEDOWNLOADERFAKEIMPL_H
