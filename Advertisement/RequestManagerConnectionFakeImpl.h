#ifndef REQUESTMANAGERCONNECTIONFAKEIMPL_H
#define REQUESTMANAGERCONNECTIONFAKEIMPL_H

#include "../../../MediaPlayer/src/Network/RequestManagerConnection.h"


class RequestManagerConnectionFakeImpl : public RequestManagerConnection
{
    Q_OBJECT
private:
    bool error_;
    int status_;
    QNetworkReply *reply_;
    QByteArray data_;
    int _redirectionCount;


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

    int redirectionCount() const;
    void setRedirectionCount(int redirectionCount);

signals:
    
public slots:

protected slots:
    void onFinisedReply();
    
};

#endif // REQUESTMANAGERCONNECTIONFAKEIMPL_H
