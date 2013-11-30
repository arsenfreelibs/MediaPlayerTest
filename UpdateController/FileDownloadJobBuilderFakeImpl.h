#ifndef FILEDOWNLOADJOBBUILDERFAKEIMPL_H
#define FILEDOWNLOADJOBBUILDERFAKEIMPL_H

#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.h"
#include "FileDownloadJobFakeImpl.h"

class FileDownloadJobBuilderFakeImpl : public FileDownloadJobBuilder
{
    Q_OBJECT

private:
    QString url_;
    QString torrentUrl_;
    QString fileName_;
    QString destinationDirectory_;

public:
    explicit FileDownloadJobBuilderFakeImpl(QObject *parent = 0);
    
    virtual void setUrl(const QString &url);
    virtual void setTorrentUrl(const QString &torrentUrl);
    virtual void setDestinationFolder(const QString &directory);
    virtual void setFileName(const QString &fileName);

    virtual FileDownloadJob* build();

    QString url() const;
    QString torrentUrl() const;
    QString fileName() const;
    QString destinationDirectory() const;


signals:
    
public slots:
    
};

#endif // FILEDOWNLOADJOBBUILDERFAKEIMPL_H
