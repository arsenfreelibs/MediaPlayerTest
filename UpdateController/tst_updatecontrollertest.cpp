#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateController.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManager.h"
#include "../../../MediaPlayer/src/Network/RequestManagerImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerConnection.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "FakeUpdateRequestSimpleImpl.h"
#include "FileDownloaderFakeImpl.h"
#include "RequestManagerConnectionFakeImpl.h"

#define AMOUNT_OF_VERSIONS_IN_RequestManagerConnectionFakeImpl 1

class UpdateControllerTest : public QObject
{
    Q_OBJECT
    
private:
    bool testResult_;
    QString newVersion_;
    QString signalStrResult_;

public:
    UpdateControllerTest();    

protected slots:
    void onUpdateExist(const QString &version);
    void onDownloadStateChanged(const QString &state);
    void onDownloadErrorPass(const QString &error);
    void onDownloadFinished();
    void onDownloadProgressUpdated(int progressValue);

    void onRequestFinished(std::vector<UpdateRequest::Version> &versions,UpdateRequest::Status status);
    void onRequestFinishedNoError(std::vector<UpdateRequest::Version> &versions,UpdateRequest::Status status);
    void onRequestFinishedParsError(std::vector<UpdateRequest::Version> &versions,UpdateRequest::Status status);
    
private Q_SLOTS:
    void testInterfaceAvailable();
    void testCreateUpdateControllerImpl();
    void testCheckAvailableUpdate_true_notSetCurrentVerToController();
    void testCheckAvailableUpdate_true();
    void testCheckAvailableUpdate_true_listOfAvailableVerFromServer();
    void testCheckAvailableUpdate_true_listOfAvailableVerFromServer_version_from_pro_file();
    void testCheckAvailableUpdate_false_listOfAvailableVerFromServer();
    void testCheckAvailableUpdate_false_emptyListOfVersions();
    void testSetGetUpdateRequest();
    void testSet_NULL_UpdateRequest();
    void testNot_SetUserProfile();
    void testSetUserProfile();
    void testCheckAvailableUpdate_true_WhenLogedIn();
    void testCheckAvailableUpdate_true_When_Not_LogedIn();

    void testDownloadNewVersion_notSetFileDownloader();
    void testDownloadNewVersion_checkJobParams();

    void testEmitSignal_DownloadStateChanged_FileDownloadListener();
    void testEmitSignal_DownloadErrorPass_FileDownloadListener();
    void testEmitSignal_DownloadFinished_FileDownloadListener();
    void testEmitSignal_DownloadProgressUpdated_FileDownloadListener();

    void testNotSetFileDownloaderEqualNULL();

    //Test classes which needed for correct work of UpdateDownloader

    void testUpdateRequestImpl_create();
    void testUpdateRequestImpl_NotSetParams();
    void testUpdateRequestImpl_SetAllParams();
    void testUpdateRequestImpl_performRequest_notSetQNetworkAccessManager();
    void testUpdateRequestImpl_performRequest_noNetworkConnection();
    void testUpdateRequestImpl_performRequest_notSetRequestManager();
    void testUpdateRequestImpl_performRequest_notSetRequestManagerConnection();
    void testUpdateRequestImpl_performRequest_returnResult();
    void testUpdateRequestImpl_performRequest_notReturnResult();
    void testUpdateRequestImpl_performRequest_returnIncorrectResult();
    void testUpdateRequestImpl_performRequest_returnIncorrectJSONValueResult();

    void testRequestManagerImpl_create();
    void testRequestManagerImpl_getNotSeted_NetworkAccessManager();
    void testRequestManagerImpl_setNetworkAccessManager();
    void testRequestManagerImpl_getNotSeted_UserProfile();
    void testRequestManagerImpl_setUserProfile();
    void testRequestManagerImpl_setCommonHttpHeaders_userProfile_NULL();
    void testRequestManagerImpl_setCommonHttpHeaders_userProfile_Seted();
    void testRequestManagerImpl_setCommonHttpHeaders_userProfile_Seted_PostRequest();
    void testRequestManagerImpl_getNotSeted_apiURL_();
    void testRequestManagerImpl_setApiURL();

    // COMPLEX TESTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void testComplex_CheckAvailableUpdate_true();


};

UpdateControllerTest::UpdateControllerTest()
{
    //given

    //when

    //expected
}

void UpdateControllerTest::onUpdateExist(const QString &version)
{
    testResult_=true;
    newVersion_ = version;
}

void UpdateControllerTest::onDownloadStateChanged(const QString &state)
{
    testResult_=true;
}

void UpdateControllerTest::onDownloadErrorPass(const QString &error)
{
    testResult_=true;
    signalStrResult_ = error;
}

void UpdateControllerTest::onDownloadFinished()
{
    testResult_=true;
}

void UpdateControllerTest::onDownloadProgressUpdated(int progressValue)
{
    testResult_=true;
}

void UpdateControllerTest::onRequestFinished(std::vector<UpdateRequest::Version> &versions, UpdateRequest::Status status)
{
    testResult_ = true;
    if(versions.capacity()>0){
        testResult_ = false;
    }
    if(status!=UpdateRequest::StatusNetworkFailure){
        testResult_ = false;
    }
}

void UpdateControllerTest::onRequestFinishedNoError(std::vector<UpdateRequest::Version> &versions, UpdateRequest::Status status)
{
    testResult_ = true;
    if(versions.capacity()!=AMOUNT_OF_VERSIONS_IN_RequestManagerConnectionFakeImpl){
        testResult_ = false;
    }
    if(status!=UpdateRequest::StatusSuccess){
        testResult_ = false;
    }
}

void UpdateControllerTest::onRequestFinishedParsError(std::vector<UpdateRequest::Version> &versions, UpdateRequest::Status status)
{
    testResult_ = true;
    if(versions.capacity()>0){
        testResult_ = false;
    }
    if(status!=UpdateRequest::StatusParseFailure){
        testResult_ = false;
    }
}

void UpdateControllerTest::testInterfaceAvailable()
{
    FileDownloadListener *fileDownloadListener;
    FileDownloadJob *fileDownloadJob;
    FileDownloader *fileDownloader;
    UpdateController *updateController;

    QVERIFY2(true, "Failure");
}

void UpdateControllerTest::testCreateUpdateControllerImpl()
{
    //when
    UpdateControllerImpl updateController;
    //Expected
    QVERIFY2(true, "Failure");
}

void UpdateControllerTest::testCheckAvailableUpdate_true_notSetCurrentVerToController()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);

    UpdateControllerImpl updateControllerImpl;    
    updateControllerImpl.setUpdateRequest(&updateRequest);

    UpdateController *updateController = &updateControllerImpl;
    testResult_ = false;
    QObject::connect(updateController, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));

    //when
    updateController->checkAvailableUpdate();

    //expected
    QVERIFY2(testResult_, "not connect to slot onUpdateExist");

}

void UpdateControllerTest::testCheckAvailableUpdate_true()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("0.0.1");

    UpdateController *updateController = &updateControllerImpl;
    testResult_ = false;
    QObject::connect(updateController, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));

    //when
    updateController->checkAvailableUpdate();

    //expected
    QVERIFY2(testResult_, "not connect to slot onUpdateExist");
}

void UpdateControllerTest::testCheckAvailableUpdate_true_listOfAvailableVerFromServer()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist3\/GoWebMediaPlayer.exe";
    ver.version = "1.0.3";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);



    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("1.0.1");

    UpdateController *updateController = &updateControllerImpl;
    QObject::connect(updateController, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));

    //when
    updateController->checkAvailableUpdate();

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString("http:\/\/dl.goweb.com\/dist3\/GoWebMediaPlayer.exe"));
    QCOMPARE(newVersion_,QString("1.0.3"));
}

void UpdateControllerTest::testCheckAvailableUpdate_true_listOfAvailableVerFromServer_version_from_pro_file()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    QString ver_app = VERSION_APP;
    updateControllerImpl.setVersion(ver_app);

    UpdateController *updateController = &updateControllerImpl;

    //when
    updateController->checkAvailableUpdate();

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString("http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe"));
}

void UpdateControllerTest::testCheckAvailableUpdate_false_listOfAvailableVerFromServer()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("1.1.1");

    UpdateController *updateController = &updateControllerImpl;

    newVersion_ = "";
    QObject::connect(updateController, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));


    //when
    updateController->checkAvailableUpdate();

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString(""));
    QCOMPARE(newVersion_,QString("")); //if new ver not available then not emit updateExist signal
}

void UpdateControllerTest::testCheckAvailableUpdate_false_emptyListOfVersions()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);


    UpdateController *updateController = &updateControllerImpl;
    testResult_ = false;
    QObject::connect(updateController, SIGNAL(updateExist(QString)),
                     this, SLOT(onUpdateExist(QString)));


    //when
    updateController->checkAvailableUpdate();

    //expected
    QVERIFY2(!testResult_, "incorrect update check");
}

void UpdateControllerTest::testSetGetUpdateRequest()
{
    //given
    UpdateControllerImpl updateController;
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest *gettedUpdateRequest;

    //when
    updateController.setUpdateRequest(&updateRequest);
    gettedUpdateRequest = updateController.updateRequest();

    //expected
    QVERIFY2(&updateRequest == gettedUpdateRequest, "setted and getted value are different");
}

void UpdateControllerTest::testSet_NULL_UpdateRequest()
{
    //given
    UpdateControllerImpl updateController;
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest *gettedUpdateRequest;

    //when
    updateController.setUpdateRequest(&updateRequest);
    updateController.setUpdateRequest(NULL);
    gettedUpdateRequest = updateController.updateRequest();

    //expected
    QVERIFY2(&updateRequest == gettedUpdateRequest, "Error, set NULL must be NOT available");
}

void UpdateControllerTest::testNot_SetUserProfile()
{
    //given
    UpdateControllerImpl updateController;
    UserProfile *userProfile;

    //when
    userProfile = updateController.userProfile();

    //expected
    QVERIFY2(userProfile==NULL, "Error, if not set UserProfile,must be return NULL");
}

void UpdateControllerTest::testSetUserProfile()
{
    //given
    UpdateControllerImpl updateController;
    UserProfile userProfile;
    UserProfile *pUserProfile;

    //when
    updateController.setUserProfile(&userProfile);
    pUserProfile = updateController.userProfile();

    //expected
    QVERIFY2(&userProfile==pUserProfile, "Error, get value not equal before setted value");
}

void UpdateControllerTest::testCheckAvailableUpdate_true_WhenLogedIn()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);

    UserProfile userProfile;

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("1.0.1");
    updateControllerImpl.setUserProfile(&userProfile);

    UpdateController *updateController = &updateControllerImpl;

    //when
    userProfile.setLoggedIn(true);

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString("http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe"));
}

void UpdateControllerTest::testCheckAvailableUpdate_true_When_Not_LogedIn()
{
    //given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);

    UserProfile userProfile;
    userProfile.setLoggedIn(true); //if not set true, then when set false, notemit signal, because was notstate changing

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("1.0.1");
    updateControllerImpl.setUserProfile(&userProfile);

    UpdateController *updateController = &updateControllerImpl;

    //when
    userProfile.setLoggedIn(false);

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString(""));
}

void UpdateControllerTest::testDownloadNewVersion_notSetFileDownloader()
{
    //Given
    FileDownloadListener fileDownloadListener;
    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    QObject::connect(&updateControllerImpl, SIGNAL(downloadErrorPass(const QString &)),
                     this, SLOT(onDownloadErrorPass(const QString &)));

    //when
    updateControllerImpl.downloadNewVersion();

    //Expected
    QVERIFY2(signalStrResult_ == QString(UpdateControllerImpl::NOT_SET_FILE_DOWNLOADER), "must emit error signal");
}

void UpdateControllerTest::testDownloadNewVersion_checkJobParams()
{
    //Given
    FakeUpdateRequestSimpleImpl updateRequest;
    UpdateRequest::Version ver;
    ver.url = "http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe";
    ver.version = "1.0.1";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist3\/GoWebMediaPlayer.exe";
    ver.version = "1.0.3";
    updateRequest.addToVersions(ver);
    ver.url = "http:\/\/dl.goweb.com\/dist2\/GoWebMediaPlayer.exe";
    ver.version = "1.0.2";
    updateRequest.addToVersions(ver);


    FileDownloadListener fileDownloadListener;

    FileDownloaderFakeImpl downloader;

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    updateControllerImpl.setFileDownloader(&downloader);
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setVersion("1.0.1");

    UpdateController *updateController = &updateControllerImpl;
    updateController->checkAvailableUpdate();

    //when
    updateController->downloadNewVersion();

    //Expected
    QVERIFY2(downloader.downloadParams().url == QString("http:\/\/dl.goweb.com\/dist3\/GoWebMediaPlayer.exe"), "not new bersion url");
    QVERIFY2(downloader.downloadParams().fileName == QString(UpdateControllerImpl::NEW_VERSION_FILE_DOWNLOAD_NAME), "incorrect file name");
    QVERIFY2(downloader.downloadParams().destinationDirectory == QString(""), "incorrect output dir");
}

void UpdateControllerTest::testEmitSignal_DownloadStateChanged_FileDownloadListener()
{
  //Given
  FileDownloadListener fileDownloadListener;
  testResult_ = false;
  UpdateControllerImpl updateControllerImpl;
  QObject::connect(&updateControllerImpl, SIGNAL(downloadStateChanged(const QString &)),
                   this, SLOT(onDownloadStateChanged(const QString &)));


  //when
  updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
  fileDownloadListener.onStateChanged();

  //expected
  QVERIFY2(testResult_, "not emit downloadStateChanged");
}

void UpdateControllerTest::testEmitSignal_DownloadErrorPass_FileDownloadListener()
{
    //Given
    FileDownloadListener fileDownloadListener;
    testResult_ = false;
    UpdateControllerImpl updateControllerImpl;
    QObject::connect(&updateControllerImpl, SIGNAL(downloadErrorPass(const QString &)),
                     this, SLOT(onDownloadErrorPass(const QString &)));


    //when
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    fileDownloadListener.onErrorPass();

    //expected
    QVERIFY2(testResult_, "not emit downloadErrorPass");
}

void UpdateControllerTest::testEmitSignal_DownloadFinished_FileDownloadListener()
{
    //Given
    FileDownloadListener fileDownloadListener;
    testResult_ = false;
    UpdateControllerImpl updateControllerImpl;
    QObject::connect(&updateControllerImpl, SIGNAL(downloadFinished()),
                     this, SLOT(onDownloadFinished()));


    //when
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    fileDownloadListener.onDownloadFinished();

    //expected
    QVERIFY2(testResult_, "not emit downloadFinished");
}

void UpdateControllerTest::testEmitSignal_DownloadProgressUpdated_FileDownloadListener()
{
    //Given
    FileDownloadListener fileDownloadListener;
    testResult_ = false;
    UpdateControllerImpl updateControllerImpl;
    QObject::connect(&updateControllerImpl, SIGNAL(downloadProgressUpdated(int)),
                     this, SLOT(onDownloadProgressUpdated(int)));


    //when
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    fileDownloadListener.onProgressUpdated(100);

    //expected
    QVERIFY2(testResult_, "not emit downloadFinished");
}

void UpdateControllerTest::testNotSetFileDownloaderEqualNULL()
{
    //Given
    UpdateControllerImpl updateControllerImpl;

    //When
    FileDownloader *fileDownloader = updateControllerImpl.fileDownloader();

    //Expected
    QVERIFY2(fileDownloader==NULL, "must be null");
}

void UpdateControllerTest::testUpdateRequestImpl_create()
{
    UpdateRequestImpl updateRequest;
}

void UpdateControllerTest::testUpdateRequestImpl_NotSetParams()
{
    //Given
    UpdateRequestImpl updateRequest;

    RequestManager *requestManager;
    RequestManagerConnection *requestManagerConnection;

    //when
    requestManager = updateRequest.requestManager();
    requestManagerConnection = updateRequest.requestManagerConnection();

    //expected
    QVERIFY2(requestManager==NULL, "must be null");
    QVERIFY2(requestManagerConnection==NULL, "must be null");

}

void UpdateControllerTest::testUpdateRequestImpl_SetAllParams()
{
    //Given
    UpdateRequestImpl updateRequest;

    RequestManager *requestManager;
    RequestManagerConnection *requestManagerConnection;

    RequestManagerImpl requestManagerImpl;
    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;

    //when
    updateRequest.setRequestManager(&requestManagerImpl);
    requestManager = updateRequest.requestManager();

    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);
    requestManagerConnection = updateRequest.requestManagerConnection();

    //expected
    QVERIFY2(requestManager==&requestManagerImpl, "must be equal to seted value");
    QVERIFY2(requestManagerConnection==&requestManagerConnectionImpl, "must be null");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_notSetQNetworkAccessManager()
{
    //given
    RequestManagerImpl requestManagerImpl;
    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;

    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with fail status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_noNetworkConnection()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(true);

    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with fail status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_notSetRequestManager()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(true);

    UpdateRequestImpl updateRequest;
//    updateRequest.setRequestManager(&requestManagerImpl); //special comment to test correct work
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with fail status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_notSetRequestManagerConnection()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(true);

    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
//    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl); //special comment to test correct work

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();

    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with fail status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_returnResult()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(false);
    requestManagerConnectionImpl.setData("{\"windows\":{\"version\":\"1.0\",\"url\":\"http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe\"},\"android\":{\"url\":\"https:\/\/play.google.com\/store\/apps\/details?id=com.goweb\"}}");


    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinishedNoError(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with success status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_notReturnResult()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(false);
    requestManagerConnectionImpl.setData("");


    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinishedParsError(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with success status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_returnIncorrectResult()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(false);
    requestManagerConnectionImpl.setData("qwerty");


    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinishedParsError(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();


    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with success status");
}

void UpdateControllerTest::testUpdateRequestImpl_performRequest_returnIncorrectJSONValueResult()
{
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(false);
    requestManagerConnectionImpl.setData("{\"windows\":3}");


    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);

    testResult_ = false;
    QObject::connect(&updateRequest, SIGNAL(requestFinished(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)),
                     this, SLOT(onRequestFinishedParsError(std::vector<UpdateRequest::Version>&, UpdateRequest::Status)));

    //when
    updateRequest.performRequest();

    //expected
    QVERIFY2(testResult_, "not emit onRequestFinished with success status");
}

void UpdateControllerTest::testRequestManagerImpl_create()
{
    RequestManagerImpl requestManager;
}

void UpdateControllerTest::testRequestManagerImpl_getNotSeted_NetworkAccessManager()
{
    //given
    RequestManagerImpl requestManager;
    QNetworkAccessManager *networkAccessManagerFromRM;

    //when
    networkAccessManagerFromRM = requestManager.networkAccessManager();

    //expected
    QVERIFY2(networkAccessManagerFromRM==NULL, "must be null");
}

void UpdateControllerTest::testRequestManagerImpl_setNetworkAccessManager()
{
    //given
    RequestManagerImpl requestManager;
    QNetworkAccessManager networkAccessManager;
    QNetworkAccessManager *networkAccessManagerFromRM;

    //when
    requestManager.setNetworkAccessManager(&networkAccessManager);
    networkAccessManagerFromRM = requestManager.networkAccessManager();

    //expected
    QCOMPARE(&networkAccessManager,networkAccessManagerFromRM);
}

void UpdateControllerTest::testRequestManagerImpl_getNotSeted_UserProfile()
{
    //given
    RequestManagerImpl requestManager;
    UserProfile *userProfile;

    //when
    userProfile = requestManager.userProfile();

    //expected
    QVERIFY2(userProfile==NULL, "must be null");
}

void UpdateControllerTest::testRequestManagerImpl_setUserProfile()
{
    //given
    RequestManagerImpl requestManager;
    UserProfile userProfile;
    UserProfile *userProfileRM;

    //when
    requestManager.setUserProfile(&userProfile);
    userProfileRM = requestManager.userProfile();

    //expected
    QCOMPARE(&userProfile,userProfileRM);
}

void UpdateControllerTest::testRequestManagerImpl_setCommonHttpHeaders_userProfile_NULL()
{
    //given
    RequestManagerImpl requestManagerImpl;

    QNetworkRequest request;
    QNetworkRequest requestEtalon;

    RequestManager *requestManager;
    requestManager = &requestManagerImpl;

    //when
    requestManager->setCommonHttpHeaders(&request,RequestManager::RequestTypeGet);

    //expected
    QCOMPARE(request,requestEtalon);

}

void UpdateControllerTest::testRequestManagerImpl_setCommonHttpHeaders_userProfile_Seted()
{
    //given
    UserProfile userProfile;
    userProfile.setToken("1234567890");

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setUserProfile(&userProfile);

    QNetworkRequest request;
    QNetworkRequest requestEtalon;
    requestEtalon.setRawHeader("X-Auth-Token", userProfile.token().toUtf8());

    RequestManager *requestManager;
    requestManager = &requestManagerImpl;

    //when
    requestManager->setCommonHttpHeaders(&request,RequestManager::RequestTypeGet);

    //expected
    QCOMPARE(request,requestEtalon);
}

void UpdateControllerTest::testRequestManagerImpl_setCommonHttpHeaders_userProfile_Seted_PostRequest()
{
    //given
    UserProfile userProfile;
    userProfile.setToken("1234567890");

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setUserProfile(&userProfile);

    QNetworkRequest request;
    QNetworkRequest requestEtalon;
    requestEtalon.setRawHeader("X-Auth-Token", userProfile.token().toUtf8());
    requestEtalon.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    RequestManager *requestManager;
    requestManager = &requestManagerImpl;

    //when
    requestManager->setCommonHttpHeaders(&request,RequestManager::RequestTypePost);

    //expected
    QCOMPARE(request,requestEtalon);
}

void UpdateControllerTest::testRequestManagerImpl_getNotSeted_apiURL_()
{
    //given
    RequestManagerImpl requestManagerImpl;
    RequestManager *requestManager;
    requestManager = &requestManagerImpl;

    //when
    QString url = requestManager->apiURL();

    //expected
    QVERIFY2(url==QString(DEFAULT_API_URL), "must be equal to defaulte");
}

void UpdateControllerTest::testRequestManagerImpl_setApiURL()
{
    //given
    RequestManagerImpl requestManagerImpl;
    RequestManager *requestManager;
    requestManager = &requestManagerImpl;

    //when
    requestManagerImpl.setApiURL("https://tvapi.goweb.com/2.0");
    QString url = requestManager->apiURL();

    //expected
    QVERIFY2(url==QString("https://tvapi.goweb.com/2.0"), "must be equal to seted");
}

void UpdateControllerTest::testComplex_CheckAvailableUpdate_true()
{
    //given
    //given
    QNetworkAccessManager networkAccessManager;

    RequestManagerImpl requestManagerImpl;
    requestManagerImpl.setNetworkAccessManager(&networkAccessManager);

    RequestManagerConnectionFakeImpl requestManagerConnectionImpl;
    requestManagerConnectionImpl.setError(false);
    requestManagerConnectionImpl.setData("{\"windows\":{\"version\":\"1.0.2\",\"url\":\"http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe\"},\"android\":{\"url\":\"https:\/\/play.google.com\/store\/apps\/details?id=com.goweb\"}}");


    UpdateRequestImpl updateRequest;
    updateRequest.setRequestManager(&requestManagerImpl);
    updateRequest.setRequestManagerConnection(&requestManagerConnectionImpl);


    UserProfile userProfile;

    FileDownloadListener fileDownloadListener;

    FileDownloaderFakeImpl downloader;

    UpdateControllerImpl updateControllerImpl;
    updateControllerImpl.setUpdateRequest(&updateRequest);
    updateControllerImpl.setUserProfile(&userProfile);
    QString ver_app = VERSION_APP;
    updateControllerImpl.setVersion(ver_app);
    updateControllerImpl.setFileDownloadListener(&fileDownloadListener);
    updateControllerImpl.setFileDownloader(&downloader);

    UpdateController *updateController = &updateControllerImpl;

    testResult_ = false;
    QObject::connect(updateController, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));

    //when
    userProfile.setLoggedIn(true); //updateController->checkAvailableUpdate();
    updateController->downloadNewVersion();

    //expected
    QCOMPARE(updateControllerImpl.updateVersion().url,QString("http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe"));
    QCOMPARE(newVersion_,QString("1.0.2"));

    QVERIFY2(downloader.downloadParams().url == QString("http:\/\/dl.goweb.com\/dist\/GoWebMediaPlayer.exe"), "not new version url");
    QVERIFY2(downloader.downloadParams().fileName == QString(UpdateControllerImpl::NEW_VERSION_FILE_DOWNLOAD_NAME), "incorrect file name");
    QVERIFY2(downloader.downloadParams().destinationDirectory == QString(""), "incorrect output dir");

}

QTEST_APPLESS_MAIN(UpdateControllerTest)

#include "tst_updatecontrollertest.moc"