#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"


class NetworkRequestManagerTest : public QObject
{
    Q_OBJECT
    
public:
    NetworkRequestManagerTest();
    
private Q_SLOTS:
    void test_create_BaseNetworkRequestManager();
    void test_setUserProfile_NetworkRequestManager();
    void test_create_NetworkRequestManager();
    void test_performAuthorizeRequest_NetworkRequestManage();

    void test_create_UserProfile();

};

NetworkRequestManagerTest::NetworkRequestManagerTest()
{
}

void NetworkRequestManagerTest::test_create_BaseNetworkRequestManager()
{
    //given
    BaseNetworkRequestManager *baseNetworkRequestManager;
    //expexted
    QVERIFY2(true, "Failure");
}

void NetworkRequestManagerTest::test_setUserProfile_NetworkRequestManager()
{
    //given
    BaseNetworkRequestManager *baseNetworkRequestManager;
    UserProfile userProfile;

    //when
//    baseNetworkRequestManager.setUserProfile(&userProfile);

    //expected
//    QCOMPARE(&userProfile, baseNetworkRequestManager.userProfile());
    QVERIFY2(false, "Failure");
}

void NetworkRequestManagerTest::test_create_NetworkRequestManager()
{
    //when
    NetworkRequestManager networkRequestManager;
    //expected
    QVERIFY2(true, "Failure");
}

void NetworkRequestManagerTest::test_performAuthorizeRequest_NetworkRequestManage()
{
    //given
    NetworkRequestManager networkRequestManager;
    UserProfile userProfile;
    networkRequestManager.setUserProfile(&userProfile);

    //when
    networkRequestManager.performAuthorizeRequest("3816459@i.ua","<fqrfkmxrfz 57,",true);
    networkRequestManager.performChannelsListRequest();

    //expected
    QVERIFY2(userProfile.loggedIn(), "Failure login");

}

void NetworkRequestManagerTest::test_create_UserProfile()
{
    //given
    UserProfile userProfile;
    //expexted
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(NetworkRequestManagerTest)

#include "tst_networkrequestmanagertest.moc"
