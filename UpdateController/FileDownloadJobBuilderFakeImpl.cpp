#include "FileDownloadJobBuilderFakeImpl.h"

FileDownloadJobBuilderFakeImpl::FileDownloadJobBuilderFakeImpl(QObject *parent) :
    FileDownloadJobBuilder(parent)
{
}

void FileDownloadJobBuilderFakeImpl::setUrl(const QString &url)
{
    url_=url;
}

void FileDownloadJobBuilderFakeImpl::setTorrentUrl(const QString &torrentUrl)
{
    torrentUrl_=torrentUrl;
}

void FileDownloadJobBuilderFakeImpl::setDestinationFolder(const QString &directory)
{
    destinationDirectory_ = directory;
}

void FileDownloadJobBuilderFakeImpl::setFileName(const QString &fileName)
{
    fileName_=fileName;
}

FileDownloadJob *FileDownloadJobBuilderFakeImpl::build()
{
    FileDownloadJobFakeImpl *job = new FileDownloadJobFakeImpl();


    return job;
}

QString FileDownloadJobBuilderFakeImpl::url() const
{
    return url_;
}

QString FileDownloadJobBuilderFakeImpl::torrentUrl() const
{
    return torrentUrl_;
}

QString FileDownloadJobBuilderFakeImpl::fileName() const
{
    return fileName_;
}

QString FileDownloadJobBuilderFakeImpl::destinationDirectory() const
{
    return destinationDirectory_;
}
