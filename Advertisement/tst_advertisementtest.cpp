#include <QString>
#include <QtTest>
#include <QDateTime>
#include "../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.h"
#include "../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h"
#include "../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.h"
#include "AdvertisementRequestFakeImpl.h"

class AdvertisementTest : public QObject
{
    Q_OBJECT

private:
    QString state_;
    QString error_;
    QString adLink_;
    bool started_;
    bool finished_;
    qint64 startTime_;
    qint64 endTime_;

public:
    AdvertisementTest();

protected slots:
    void onStateChanged(const QString &state);
    void onErrorPass(const QString &error);
    void onRequestFinished(const QString &adLink);
    void onStarted();
    void onFinished();
    
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
}

void AdvertisementTest::onStarted()
{
    started_ = true;
    startTime_ = QDateTime::currentMSecsSinceEpoch();
}

void AdvertisementTest::onFinished()
{
    finished_ = true;
    endTime_ = QDateTime::currentMSecsSinceEpoch();
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

    AdvertisementRequestFakeImpl advertisementRequestFakeImpl;
    advertisementControllerImpl.setAdRequest(&advertisementRequestFakeImpl);

    resetStateError();

    //when
    advertisementController->requetToPlayAdFromVastResouce("");

    //expected
    QCOMPARE(state_,AdvertisementControllerImpl::STATE_ABORTED);
    QCOMPARE(error_,AdvertisementControllerImpl::ERR_NETWORK);
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
    QObject::connect(&advertisementControllerImpl, SIGNAL(started()),
                     this, SLOT(onStarted()));


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
}

void AdvertisementTest::resetStateError()
{
    state_ = "";
    error_= "";
}

QTEST_APPLESS_MAIN(AdvertisementTest)

#include "tst_advertisementtest.moc"
