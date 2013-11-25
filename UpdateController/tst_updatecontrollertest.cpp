#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateController.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "FakeUpdateRequestSimpleImpl.h"

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

    void testEmitSignal_DownloadStateChanged_FileDownloadListener();
    void testEmitSignal_DownloadErrorPass_FileDownloadListener();
    void testEmitSignal_DownloadFinished_FileDownloadListener();
    void testEmitSignal_DownloadProgressUpdated_FileDownloadListener();

    void testNotSetFileDownloaderEqualNULL();
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

QTEST_APPLESS_MAIN(UpdateControllerTest)

#include "tst_updatecontrollertest.moc"
