#include "FileDownloadJobFakeImpl.h"

FileDownloadJobFakeImpl::FileDownloadJobFakeImpl(QObject *parent) :
    FileDownloadJob(parent)
{
}

void FileDownloadJobFakeImpl::setUrl(const QString &url)
{
}

QString FileDownloadJobFakeImpl::url() const
{
}

void FileDownloadJobFakeImpl::setTorrentUrl(const QString &torrentUrl)
{
}

QString FileDownloadJobFakeImpl::torrentUrl() const
{
}

void FileDownloadJobFakeImpl::setDestinationFolder(const QString &directory)
{
}

QString FileDownloadJobFakeImpl::destinationFolder() const
{
}

void FileDownloadJobFakeImpl::setFileName(const QString &directory)
{
}

QString FileDownloadJobFakeImpl::fileName() const
{
}

FileDownloadJob::State FileDownloadJobFakeImpl::state() const
{
}

QString FileDownloadJobFakeImpl::stateString() const
{
}

FileDownloadJob::Error FileDownloadJobFakeImpl::error() const
{
}

QString FileDownloadJobFakeImpl::errorString() const
{
}

void FileDownloadJobFakeImpl::start()
{
    emit stateChanged();

    emit errorPass();

    emit progressUpdated(33);

    emit downloadFinished();
}

void FileDownloadJobFakeImpl::stop()
{
    emit stateChanged();
    emit downloadFinished();
}

void FileDownloadJobFakeImpl::setPaused(bool paused)
{
    emit stateChanged();
}

