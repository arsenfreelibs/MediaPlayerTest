#ifndef NETWORKPROTOCOLTESTER_H
#define NETWORKPROTOCOLTESTER_H

#include <QObject>
#include <QDebug>
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"

class NetworkProtocolTester : public QObject
{
    Q_OBJECT

private:
    NetworkRequestManager networkRequestManager_;
    UserProfile userProfile_;

public:
    explicit NetworkProtocolTester(QObject *parent = 0);
    
signals:
    
public slots:
    void execute();

    void onLoginStatusChange(bool isLogin);
    void onChannelsListResponse(std::vector<PlaylistModelEntry> &entries);
    
};

#endif // NETWORKPROTOCOLTESTER_H
