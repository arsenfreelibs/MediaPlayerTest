#include "FileDownloaderFakeImpl.h"

FileDownloaderFakeImpl::FileDownloaderFakeImpl(QObject *parent) :
    FileDownloader(parent),stopOk_(false)
{
}

FileDownloader::JobID FileDownloaderFakeImpl::addDownloading(const FileDownloader::JobDownloadParams &downloadParams, FileDownloadListener *listener)
{
    downloadParams_ = downloadParams;
    listener->onDownloadFinished();
    id_=QDateTime::currentMSecsSinceEpoch();
    return id_;
}

FileDownloader::Status FileDownloaderFakeImpl::stopDownloading(FileDownloader::JobID id)
{
    stopOk_ = (id_==(id));
}

FileDownloader::JobDownloadParams FileDownloaderFakeImpl::downloadParams() const
{
    return downloadParams_;
}

void FileDownloaderFakeImpl::setDownloadParams(const JobDownloadParams &downloadParams)
{
    downloadParams_ = downloadParams;
}

bool FileDownloaderFakeImpl::isCorrectStopJobId()
{
    return stopOk_;
}
