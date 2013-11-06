#ifndef NETWORKFILEREQUESTMANAGER_H
#define NETWORKFILEREQUESTMANAGER_H
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"

class NetworkFileRequestManager : public NetworkRequestManager
{
    Q_OBJECT
public:
    explicit NetworkFileRequestManager(QObject *parent = 0);

    void performFilmsListRequest();
    
signals:
    
public slots:

protected slots:
//    void processFilmsListResponse(NetworkRequestManagerConnection *connection, bool error, int status);

    
};

#endif // NETWORKFILEREQUESTMANAGER_H
