#include "FileDownloaderTestFakeImpl.h"

FileDownloaderTestFakeImpl::FileDownloaderTestFakeImpl(QObject *parent) :
    FileDownloaderImpl(parent)
{
}

int FileDownloaderTestFakeImpl::jobCount()
{
    return fileDownloadJobs_.size();
}
