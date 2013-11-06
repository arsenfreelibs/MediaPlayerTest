#include "NetworkFileRequestManager.h"

NetworkFileRequestManager::NetworkFileRequestManager(QObject *parent) :
    NetworkRequestManager(parent)
{
}

void NetworkFileRequestManager::performFilmsListRequest()
{
    QUrl url(apiURL_ + "/channels/list");
    QNetworkRequest request(url);
    if (!userProfile_->token().isEmpty())
        request.setRawHeader("X-Auth-Token", userProfile_->token().toUtf8());
    request.setRawHeader("Accept-Language", /*Settings::sharedInstance()->language().toLocal8Bit()*/"ru");  // TODO put to separate method, which constract HTTP header

    QNetworkReply *reply = networkAccessManager_.get(request);
    NetworkRequestManagerConnection *connection = new NetworkRequestManagerConnection(reply);
//    QObject::connect(connection, SIGNAL(finished(NetworkRequestManagerConnection *, bool,int)),
//                     this, SLOT(processFilmsListResponse(NetworkRequestManagerConnection*,bool,int)));
}
