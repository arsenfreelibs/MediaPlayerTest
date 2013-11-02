#include "NetworkProtocolTester.h"

NetworkProtocolTester::NetworkProtocolTester(QObject *parent) :
    QObject(parent)
{
    networkRequestManager_.setUserProfile(&userProfile_);

    QObject::connect(&userProfile_, SIGNAL(loggedInChanged(bool)),
                     this, SLOT(onLoginStatusChange(bool)));

    QObject::connect(&networkRequestManager_, SIGNAL(channelsListResponseProcessed(std::vector<PlaylistModelEntry>&)),
                     this, SLOT(onChannelsListResponse(std::vector<PlaylistModelEntry>&)));
}

void NetworkProtocolTester::execute()
{
    networkRequestManager_.performAuthorizeRequest("3816459@i.ua","<fqrfkmcrfz 57,",true);    
}

void NetworkProtocolTester::onLoginStatusChange(bool isLogin)
{
    if(isLogin){
        networkRequestManager_.performChannelsListRequest();
    }
}

void NetworkProtocolTester::onChannelsListResponse(std::vector<PlaylistModelEntry> &entries)
{
    foreach(PlaylistModelEntry entry, entries){
        qDebug().nospace() << "title = " << entry.title();
    }
}
