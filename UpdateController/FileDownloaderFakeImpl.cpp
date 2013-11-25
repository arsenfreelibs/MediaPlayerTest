#include "FileDownloaderFakeImpl.h"

FileDownloaderFakeImpl::FileDownloaderFakeImpl(QObject *parent) :
    FileDownloader(parent)
{
}

FileDownloader::JobID FileDownloaderFakeImpl::addDownloading(const FileDownloader::JobDownloadParams &downloadParams, FileDownloadListener *listener)
{
    downloadParams_ = downloadParams;
    listener->onDownloadFinished();
}

FileDownloader::JobDownloadParams FileDownloaderFakeImpl::downloadParams() const
{
    return downloadParams_;
}

void FileDownloaderFakeImpl::setDownloadParams(const JobDownloadParams &downloadParams)
{
    downloadParams_ = downloadParams;
}
