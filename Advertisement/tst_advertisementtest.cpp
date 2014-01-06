#include <QString>
#include <QtTest>
#include <QDateTime>
#include "../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.h"
#include "../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h"
#include "../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequestImpl.h"
#include "../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerImpl.h"
#include "AdvertisementRequestFakeImpl.h"
#include "RequestManagerConnectionFakeImpl.h"

class AdvertisementTest : public QObject
{
    Q_OBJECT

private:
    QString state_;
    QString error_;
    QString adLink_;
    bool started_;
    bool finished_;
    bool isOnRequestFinished_;
    qint64 startTime_;
    qint64 endTime_;

    AdvertisementRequest::Status rqStatus_;
    AdvertisementRequest::AdData adData_;

    AdvertisementController *advertisementController_;


public:
    AdvertisementTest();

protected slots:
    void onStateChanged(const QString &state);
    void onErrorPass(const QString &error);
    void onRequestFinished(const QString &adLink);
    void onRequestFinished_startPlay(const QString &adLink);
    void onStarted();
    void onFinished();

    void onFinishedGetData(const AdvertisementRequest::AdData &adData,AdvertisementRequest::Status status);
    void onFinishedRqstToStartingPlay(AdvertisementRequest::Status status);
    
private Q_SLOTS:
    void test_initInterfaces();

    void test_getState_idle();

    void test_getLastError_NOERROR();

    void test_setGetAdRequest();

    void test_requetToPlayAdFromVastResouce_success();
    void test_requetToPlayAdFromVastResouce_notSetAdRequest();
    void test_requetToPlayAdFromVastResouce_netErr();

    void test_requetToStartPlayAd_notGetAdData();
    void test_requetToStartPlayAd_notSetAdRequest();
    void test_requetToStartPlayAd_started();
    void test_requetToStartPlayAd_started_andProblemWithNet();

    void test_AdvertisementRequestImpl_create();
    void test_AdvertisementRequestImpl_checkInitState();
    void test_performGetDataRequest_notSetRequestManagerAndRequestManagerConnection();
    void test_performGetDataRequest_ok();
    void test_performGetDataRequest_parsError();
    void test_performGetDataRequest_netError();

    void test_performStartPlayRequest_ok();


    void test_complex_ok();

//    //when

//    //expected
//    QVERIFY2(false, "Not impl");


private:
    void resetStateError();

};

AdvertisementTest::AdvertisementTest():
    state_(""),error_("")
{
}

void AdvertisementTest::onStateChanged(const QString &state)
{
    state_=state;
}

void AdvertisementTest::onErrorPass(const QString &error)
{
    error_ = error;
}

void AdvertisementTest::onRequestFinished(const QString &adLink)
{
    adLink_=adLink;
    isOnRequestFinished_ = true;
}

void AdvertisementTest::onRequestFinished_startPlay(const QString &adLink)
{
    adLink_=adLink;
    isOnRequestFinished_ = true;
    advertisementController_->requetToStartPlayAd();
}

void AdvertisementTest::onStarted()
{
    started_ = true;
}

void AdvertisementTest::onFinished()
{
    finished_ = true;
}

void AdvertisementTest::onFinishedGetData(const AdvertisementRequest::AdData &adData, AdvertisementRequest::Status status)
{
    rqStatus_ = status;
    adData_ = adData;
}

void AdvertisementTest::onFinishedRqstToStartingPlay(AdvertisementRequest::Status status)
{
    rqStatus_ = status;
}

void AdvertisementTest::test_initInterfaces()
{
    //When
    AdvertisementController *advertisementController;
    AdvertisementRequest *advertisementRequest;

    //Expected
    QVERIFY2(true, "Failure initInterfaces");
}

void AdvertisementTest::test_getState_idle()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    resetStateError();

    //when
    QString state = advertisementController->getState();


    //expected
    QVERIFY2(state == AdvertisementControllerImpl::STATE_IDLE, "Not in idle state");
}

void AdvertisementTest::test_getLastError_NOERROR()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    resetStateError();

    //when
    QString error = advertisementController->getLastError();


    //expected
    QCOMPARE(error,AdvertisementControllerImpl::ERR_NOERROR);
}

void AdvertisementTest::test_setGetAdRequest()
{
    //Given
    AdvertisementControllerImpl advertisementControllerImpl;
    AdvertisementRequest *adRequest_afterInit = advertisementControllerImpl.getAdRequest();

    //when

    //expected
    QVERIFY2(adRequest_afterInit==NULL, "Not adRequest after init");
}

void AdvertisementTest::test_requetToPlayAdFromVastResouce_success()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));

    QObject::connect(&advertisementControllerImpl, SIGNAL(requestFinished(const QString &)),
                     this, SLOT(onRequestFinished(const QString &)));


    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();
    adLink_="";
    //when
    advertisementController->requetToPlayAdFromVastResouce("http://ad.goweb.com/code/bc?referal=REFERAL_ID");

    //expected
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_REQUEST_PROCESSED_FINISHED);
    QCOMPARE(adLink_,QString(FAKE_AD_LINK));
}

void AdvertisementTest::test_requetToPlayAdFromVastResouce_notSetAdRequest()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(errorPass(const QString &)),
                     this, SLOT(onErrorPass(const QString &)));


    resetStateError();

    //when
    advertisementController->requetToPlayAdFromVastResouce("");

    //expected
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_,AdvertisementControllerImpl::ERR_NOT_SET_REQUEST);
}

void AdvertisementTest::test_requetToPlayAdFromVastResouce_netErr()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(errorPass(const QString &)),
                     this, SLOT(onErrorPass(const QString &)));

    QObject::connect(&advertisementControllerImpl, SIGNAL(requestFinished(const QString &)),
                     this, SLOT(onRequestFinished(const QString &)));

    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();
    isOnRequestFinished_ = false;
    adLink_=FAKE_AD_LINK;


    //when
    advertisementController->requetToPlayAdFromVastResouce("");

    //expected
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_,AdvertisementControllerImpl::ERR_NETWORK);
    QVERIFY2(isOnRequestFinished_,"must emit requestFinished signal with empty data and error");
    QCOMPARE(adLink_,QString(""));
}

void AdvertisementTest::test_requetToStartPlayAd_notGetAdData()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(errorPass(const QString &)),
                     this, SLOT(onErrorPass(const QString &)));

    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();

    //when
    advertisementController->requetToStartPlayAd();

    //expected
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_,AdvertisementControllerImpl::ERR_NO_AD_DATA);
}

void AdvertisementTest::test_requetToStartPlayAd_notSetAdRequest()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(errorPass(const QString &)),
                     this, SLOT(onErrorPass(const QString &)));


    resetStateError();

    //when
    advertisementController->requetToStartPlayAd();

    //expected
    QCOMPARE(state_ ,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_,AdvertisementControllerImpl::ERR_NOT_SET_REQUEST);
}

void AdvertisementTest::test_requetToStartPlayAd_started()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));

    QObject::connect(&advertisementControllerImpl, SIGNAL(requestFinished(const QString &)),
                     this, SLOT(onRequestFinished(const QString &)));

    started_ = false;
    QObject::connect(&advertisementControllerImpl, SIGNAL(started()),
                     this, SLOT(onStarted()));


    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();
    adLink_="";
    advertisementController->requetToPlayAdFromVastResouce(FAKE_VAST_LINK);

    //when
    advertisementController->requetToStartPlayAd();

    //expected
    QVERIFY2(started_, "Not start play Ad");
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_STARTED);
}

void AdvertisementTest::test_requetToStartPlayAd_started_andProblemWithNet()
{
    //given
    AdvertisementController *advertisementController;
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(errorPass(const QString &)),
                     this, SLOT(onErrorPass(const QString &)));
    QObject::connect(&advertisementControllerImpl, SIGNAL(requestFinished(const QString &)),
                     this, SLOT(onRequestFinished(const QString &)));

    started_ = false;
    finished_ = false;
    QObject::connect(&advertisementControllerImpl, SIGNAL(started()),
                     this, SLOT(onStarted()));
    QObject::connect(&advertisementControllerImpl, SIGNAL(finished()),
                     this, SLOT(onFinished()));


    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();
    adLink_="";
    advertisementController->requetToPlayAdFromVastResouce(FAKE_VAST_BAD_PLAY_LINK);

    //when
    advertisementController->requetToStartPlayAd();

    //expected
    QVERIFY2(!started_, "Not start play Ad");
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_ ,AdvertisementControllerImpl::ERR_NETWORK);
    QVERIFY2(finished_, "must finish playing");
}

void AdvertisementTest::test_AdvertisementRequestImpl_create()
{
    //when
    AdvertisementRequestImpl advertisementRequestImpl;
    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    //expected
    QVERIFY2(advertisementRequest != NULL,"not null");
}

void AdvertisementTest::test_AdvertisementRequestImpl_checkInitState()
{
    //given
    AdvertisementRequestImpl advertisementRequestImpl;

    //when
    RequestManager *rm = advertisementRequestImpl.requestManager();
    RequestManagerConnection *rmc = advertisementRequestImpl.requestManagerConnection();

    //expected
    QCOMPARE(rm,(RequestManager *)NULL);
    QCOMPARE(rmc,(RequestManagerConnection *)NULL);
}

void AdvertisementTest::test_performGetDataRequest_notSetRequestManagerAndRequestManagerConnection()
{
    //given
    AdvertisementRequestImpl advertisementRequestImpl;
    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    QObject::connect(advertisementRequest, SIGNAL(finishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)),
                     this, SLOT(onFinishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)));

    rqStatus_ = AdvertisementRequest::StatusSuccess;

//    RequestManagerConnectionFakeImpl requestManagerConnection;
//    RequestManagerImpl requestManager;

    //when
    advertisementRequest->performGetDataRequest(FAKE_VAST_LINK);

    //expected
    QCOMPARE(rqStatus_,AdvertisementRequest::StatusInternalError);
    QCOMPARE(adData_.clickUrl,QString(""));
    QCOMPARE(adData_.duration,0);
    QCOMPARE(adData_.startUrl,QString(""));
    QCOMPARE(adData_.videoUrl,QString(""));
}

void AdvertisementTest::test_performGetDataRequest_ok()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl getDataRequestManagerConnection;
    getDataRequestManagerConnection.setError(false);
    getDataRequestManagerConnection.setData("<VAST version=\"2.0\"><Ad id=\"1\"><InLine><AdSystem>GoWebAdvert</AdSystem><AdTitle><![CDATA[ GoWeb Advert ]]></AdTitle><Impression><![CDATA[http://ad.goweb.com/bc/track?e=impression&b=52a86218796086162d008355&ref=52a86218796086162d008353]]></Impression><Creatives><Creative><Linear><Duration>00:30</Duration><VideoClips><ClickThrough><![CDATA[http://ad.goweb.com/bc/track?e=click&b=52a86218796086162d008355&ref=52a86218796086162d008353]]></ClickThrough></VideoClips><MediaFiles><MediaFile type=\"media/mp4\" delivery=\"progressive\" width=\"1280\" height=\"720\"><![CDATA[http://ytv.su/ad/ad1.mp4?pepsi]]></MediaFile></MediaFiles></Linear></Creative></Creatives></InLine></Ad></VAST>");

//    getDataRequestManagerConnection.setData("<VAST version=\"2.0\"><Ad id=\"1\"><InLine><AdSystem>GoWebAdvert</AdSystem><AdTitle><![CDATA[ GoWeb Advert ]]></AdTitle><Impression><![CDATA[ http://ad.goweb.com/bc/track?e=impression&b=52a86218796086162d008355&ref=52a86218796086162d008353 ]]></Impression><Creatives><Creative><Linear><Duration>00:30</Duration><VideoClips><ClickThrough><![CDATA[ http://ad.goweb.com/bc/track?e=click&b=52a86218796086162d008355&ref=52a86218796086162d008353 ]]></ClickThrough></VideoClips><MediaFiles><MediaFile type=\"media/mp4\" delivery=\"progressive\" width=\"1280\" height=\"720\"><![CDATA[ http://ytv.su/ad/ad1.mp4?pepsi ]]></MediaFile></MediaFiles></Linear></Creative></Creatives></InLine></Ad></VAST>");


    RequestManagerConnectionFakeImpl notificationRequestManagerConnection;
    notificationRequestManagerConnection.setError(false);
    notificationRequestManagerConnection.setData("");

    AdvertisementRequestImpl advertisementRequestImpl;
    advertisementRequestImpl.setRequestManager(&requestManagerImpl);
    advertisementRequestImpl.setGetDataRequestManagerConnection(&getDataRequestManagerConnection);
    advertisementRequestImpl.setNotificationRequestManagerConnection(&notificationRequestManagerConnection);

    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    QObject::connect(advertisementRequest, SIGNAL(finishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)),
                     this, SLOT(onFinishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)));

    rqStatus_ = AdvertisementRequest::StatusUnknownServerError;

    //when
    advertisementRequest->performGetDataRequest(FAKE_VAST_LINK);

    //expected
    QCOMPARE(rqStatus_,AdvertisementRequest::StatusSuccess);
    QCOMPARE(adData_.startUrl,QString("http://ad.goweb.com/bc/track?e=impression&b=52a86218796086162d008355&ref=52a86218796086162d008353"));
    QCOMPARE(adData_.clickUrl,QString("http://ad.goweb.com/bc/track?e=click&b=52a86218796086162d008355&ref=52a86218796086162d008353"));
    QCOMPARE(adData_.duration,30);
    QCOMPARE(adData_.videoUrl,QString("http://ytv.su/ad/ad1.mp4?pepsi"));
}

void AdvertisementTest::test_performGetDataRequest_parsError()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl getDataRequestManagerConnection;
    getDataRequestManagerConnection.setError(false);
    getDataRequestManagerConnection.setData("<NOTVAST version=\"2.0\"> </NOTVAST>");

    RequestManagerConnectionFakeImpl notificationRequestManagerConnection;
    notificationRequestManagerConnection.setError(false);
    notificationRequestManagerConnection.setData("");

    AdvertisementRequestImpl advertisementRequestImpl;
    advertisementRequestImpl.setRequestManager(&requestManagerImpl);
    advertisementRequestImpl.setGetDataRequestManagerConnection(&getDataRequestManagerConnection);
    advertisementRequestImpl.setNotificationRequestManagerConnection(&notificationRequestManagerConnection);

    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    QObject::connect(advertisementRequest, SIGNAL(finishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)),
                     this, SLOT(onFinishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)));

    rqStatus_ = AdvertisementRequest::StatusUnknownServerError;

    //when
    advertisementRequest->performGetDataRequest(FAKE_VAST_LINK);

    //expected
    QCOMPARE(rqStatus_,AdvertisementRequest::StatusParseFailure);
    QCOMPARE(adData_.clickUrl,QString(""));
    QCOMPARE(adData_.duration,0);
    QCOMPARE(adData_.startUrl,QString(""));
    QCOMPARE(adData_.videoUrl,QString(""));
}

void AdvertisementTest::test_performGetDataRequest_netError()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl getDataRequestManagerConnection;
    getDataRequestManagerConnection.setError(true);
    getDataRequestManagerConnection.setData("");

    RequestManagerConnectionFakeImpl notificationRequestManagerConnection;
    notificationRequestManagerConnection.setError(false);
    notificationRequestManagerConnection.setData("");

    AdvertisementRequestImpl advertisementRequestImpl;
    advertisementRequestImpl.setRequestManager(&requestManagerImpl);
    advertisementRequestImpl.setGetDataRequestManagerConnection(&getDataRequestManagerConnection);
    advertisementRequestImpl.setNotificationRequestManagerConnection(&notificationRequestManagerConnection);

    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    QObject::connect(advertisementRequest, SIGNAL(finishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)),
                     this, SLOT(onFinishedGetData(const AdvertisementRequest::AdData &,AdvertisementRequest::Status)));

    rqStatus_ = AdvertisementRequest::StatusUnknownServerError;

    //when
    advertisementRequest->performGetDataRequest(FAKE_VAST_LINK);

    //expected
    QCOMPARE(rqStatus_,AdvertisementRequest::StatusNetworkFailure);
    QCOMPARE(adData_.clickUrl,QString(""));
    QCOMPARE(adData_.duration,0);
    QCOMPARE(adData_.startUrl,QString(""));
    QCOMPARE(adData_.videoUrl,QString(""));
}

void AdvertisementTest::test_performStartPlayRequest_ok()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl getDataRequestManagerConnection;
    getDataRequestManagerConnection.setError(false);
    getDataRequestManagerConnection.setData("<VAST version=\"2.0\"> </VAST>");

    RequestManagerConnectionFakeImpl notificationRequestManagerConnection;
    notificationRequestManagerConnection.setError(false);
    notificationRequestManagerConnection.setData("");

    AdvertisementRequestImpl advertisementRequestImpl;
    advertisementRequestImpl.setRequestManager(&requestManagerImpl);
    advertisementRequestImpl.setGetDataRequestManagerConnection(&getDataRequestManagerConnection);
    advertisementRequestImpl.setNotificationRequestManagerConnection(&notificationRequestManagerConnection);

    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    QObject::connect(advertisementRequest, SIGNAL(finishedRqstToStartingPlay(AdvertisementRequest::Status)),
                     this, SLOT(onFinishedRqstToStartingPlay(AdvertisementRequest::Status)));

    rqStatus_ = AdvertisementRequest::StatusUnknownServerError;

    //when
    advertisementRequest->performStartPlayRequest(FAKE_AD_START_LINK);

    //expected
    QCOMPARE(rqStatus_,AdvertisementRequest::StatusSuccess);
}

void AdvertisementTest::test_complex_ok()
{
    //given
    AdvertisementControllerImpl advertisementControllerImpl;

    advertisementController_ = &advertisementControllerImpl;

    QObject::connect(&advertisementControllerImpl, SIGNAL(stateChanged(const QString &)),
                     this, SLOT(onStateChanged(const QString &)));

    QObject::connect(&advertisementControllerImpl, SIGNAL(requestFinished(const QString &)),
                     this, SLOT(onRequestFinished_startPlay(const QString &)));

    started_ = false;
    QObject::connect(&advertisementControllerImpl, SIGNAL(started()),
                     this, SLOT(onStarted()));

    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl getDataRequestManagerConnection;
    getDataRequestManagerConnection.setError(false);
    getDataRequestManagerConnection.setData("<VAST version=\"2.0\"><Ad id=\"1\"><InLine><AdSystem>GoWebAdvert</AdSystem><AdTitle><![CDATA[ GoWeb Advert ]]></AdTitle><Impression><![CDATA[ http://ad.goweb.com/bc/track?e=impression&b=52a86218796086162d008355&ref=52a86218796086162d008353 ]]></Impression><Creatives><Creative><Linear><Duration>00:30</Duration><VideoClips><ClickThrough><![CDATA[http://ad.goweb.com/bc/track?e=click&b=52a86218796086162d008355&ref=52a86218796086162d008353]]></ClickThrough></VideoClips><MediaFiles><MediaFile type=\"media/mp4\" delivery=\"progressive\" width=\"1280\" height=\"720\"><![CDATA[http://ytv.su/ad/ad1.mp4?pepsi]]></MediaFile></MediaFiles></Linear></Creative></Creatives></InLine></Ad></VAST>");

    RequestManagerConnectionFakeImpl notificationRequestManagerConnection;
    notificationRequestManagerConnection.setError(false);
    notificationRequestManagerConnection.setData("");

    AdvertisementRequestImpl advertisementRequestImpl;
    advertisementRequestImpl.setRequestManager(&requestManagerImpl);
    advertisementRequestImpl.setGetDataRequestManagerConnection(&getDataRequestManagerConnection);
    advertisementRequestImpl.setNotificationRequestManagerConnection(&notificationRequestManagerConnection);

    AdvertisementRequest *advertisementRequest = &advertisementRequestImpl;

    advertisementControllerImpl.setAdRequest(advertisementRequest);

    resetStateError();
    adLink_="";
    isOnRequestFinished_ = false;
    started_=false;

    //when

    advertisementController_->requetToPlayAdFromVastResouce(FAKE_VAST_LINK);
    QString clickUrl = advertisementController_->getClickUrl();

    //expected
    QVERIFY2(isOnRequestFinished_,"must emit requestFinished signal with empty data and error");
    QCOMPARE(adLink_,QString("http://ytv.su/ad/ad1.mp4?pepsi"));
    QCOMPARE(clickUrl,QString("http://ad.goweb.com/bc/track?e=click&b=52a86218796086162d008355&ref=52a86218796086162d008353"));
    QVERIFY2(started_, "Not start play Ad");
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_STARTED);
}

void AdvertisementTest::resetStateError()
{
    state_ = "";
    error_= "";
}

QTEST_APPLESS_MAIN(AdvertisementTest)

#include "tst_advertisementtest.moc"
