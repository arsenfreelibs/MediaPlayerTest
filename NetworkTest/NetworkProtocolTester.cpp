#include "NetworkProtocolTester.h"

NetworkProtocolTester::NetworkProtocolTester(QObject *parent) :
    QObject(parent)
{
    networkRequestManager_.setUserProfile(&userProfile_);
}

void NetworkProtocolTester::execute()
{
    networkRequestManager_.performAuthorizeRequest("3816459@i.ua","<fqrfkmxrfz 57,",true);
//    networkRequestManager_.performChannelsListRequest();
}
