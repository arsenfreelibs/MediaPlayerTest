#include "RequestManagerConnectionFakeImpl.h"

RequestManagerConnectionFakeImpl::RequestManagerConnectionFakeImpl(QObject *parent) :
    RequestManagerConnection(parent),_error(false),_status(0),_urlStr("")
{
}

QByteArray &RequestManagerConnectionFakeImpl::downloadedData()
{
    return _dataOfResponse;
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
    _reply = reply;
    onFinisedReply(); // must be emited by reply: QObject::connect(reply, SIGNAL(finished()), this, SLOT(onFinisedReply()));
}

void RequestManagerConnectionFakeImpl::onFinisedReply()
{
    if(_urlStr==""){
        _dataOfResponse = _data;
    }else{
        if(_urlStr == _reply->url().toString()){
            _dataOfResponse = _data;
        }else{
            _dataOfResponse.clear();
        }
    }
    emit finished();
    if(_reply != NULL) _reply->deleteLater();
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
    return _status;
}

void RequestManagerConnectionFakeImpl::setStatus(int ststus)
{
    _status = ststus;
}

bool RequestManagerConnectionFakeImpl::error() const
{
    return _error;
}

void RequestManagerConnectionFakeImpl::setError(bool error)
{
    _error = error;
}

QByteArray RequestManagerConnectionFakeImpl::data() const
{
    return _data;
}

void RequestManagerConnectionFakeImpl::setData(const QByteArray &data)
{
    _data = data;
}

QString RequestManagerConnectionFakeImpl::urlStr() const
{
    return _urlStr;
}

void RequestManagerConnectionFakeImpl::setUrlStr(const QString &urlStr)
{
    _urlStr = urlStr;
}
