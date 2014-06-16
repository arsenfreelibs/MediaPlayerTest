#ifndef REQUESTMANAGERCONNECTIONFAKEIMPL_H
#define REQUESTMANAGERCONNECTIONFAKEIMPL_H

#include "../../../MediaPlayer/src/Network/RequestManagerConnection.h"


class RequestManagerConnectionFakeImpl : public RequestManagerConnection
{
    Q_OBJECT
public:
    explicit RequestManagerConnectionFakeImpl(QObject *parent = 0);
    
    virtual QByteArray &downloadedData();
    virtual QNetworkReply *reply();
    virtual QUrl getRedirectedUrl();
    virtual void setReply(QNetworkReply *reply);
    virtual bool getError();
    virtual int getStatusCode();


    bool error() const;
    void setError(bool error);

    int status() const;
    void setStatus(int status);

    QByteArray data() const;
    void setData(const QByteArray &data);

    QString urlStr() const;
    void setUrlStr(const QString &urlStr);

signals:
    
public slots:

protected slots:
    void onFinisedReply();
    
private:
    bool _error;
    int _status;
    QNetworkReply *_reply;
    QByteArray _data;
    QByteArray _dataOfResponse;
    QString _urlStr;

};

#endif // REQUESTMANAGERCONNECTIONFAKEIMPL_H
