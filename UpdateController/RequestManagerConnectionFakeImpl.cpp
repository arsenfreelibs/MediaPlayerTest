#include "RequestManagerConnectionFakeImpl.h"

RequestManagerConnectionFakeImpl::RequestManagerConnectionFakeImpl(QObject *parent) :
    RequestManagerConnection(parent),error_(false),status_(0)
{
}

QByteArray &RequestManagerConnectionFakeImpl::downloadedData()
{
    return data_;
}

QNetworkReply *RequestManagerConnectionFakeImpl::reply()
{
    return NULL;
}

QUrl RequestManagerConnectionFakeImpl::getRedirectedUrl()
{     
     return QUrl();
}

void RequestManagerConnectionFakeImpl::setReply(QNetworkReply *reply)
{
    reply_ = reply;
    onFinisedReply(); // must be emited by reply: QObject::connect(reply, SIGNAL(finished()), this, SLOT(onFinisedReply()));
}

void RequestManagerConnectionFakeImpl::onFinisedReply()
{
    emit finished();
    if(reply_ != NULL) reply_->deleteLater();
}

bool RequestManagerConnectionFakeImpl::getError()
{
    return error();
}

int RequestManagerConnectionFakeImpl::getStatusCode()
{
    return status();
}

int RequestManagerConnectionFakeImpl::status() const
{
    return status_;
}

void RequestManagerConnectionFakeImpl::setStatus(int ststus)
{
    status_ = ststus;
}

bool RequestManagerConnectionFakeImpl::error() const
{
    return error_;
}

void RequestManagerConnectionFakeImpl::setError(bool error)
{
    error_ = error;
}

QByteArray RequestManagerConnectionFakeImpl::data() const
{
    return data_;
}

void RequestManagerConnectionFakeImpl::setData(const QByteArray &data)
{
    data_ = data;
}
