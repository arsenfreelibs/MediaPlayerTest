#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateController.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"
#include "FakeUpdateRequestSimpleImpl.h"

class UpdateControllerTest : public QObject
{
    Q_OBJECT
    
private:
    bool testResult_;

public:
    UpdateControllerTest();    

protected slots:
    void onUpdateExist();
    
private Q_SLOTS:
    void testInterfaceAvailable();
    void testCreateUpdateControllerImpl();
    void testCheckAvailableUpdate_true();
    void testSetGetUpdateRequest();
};

UpdateControllerTest::UpdateControllerTest()
{
    //given

    //when

    //expected
}

void UpdateControllerTest::onUpdateExist()
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

void UpdateControllerTest::testCheckAvailableUpdate_true()
{
    //given
    UpdateController *updateController = new UpdateControllerImpl;
    testResult_ = false;
    QObject::connect(updateController, SIGNAL(updateExist()),
                     this, SLOT(onUpdateExist()));

    //when
    updateController->checkAvailableUpdate();

    //expected
    QVERIFY2(testResult_, "not connect to slot onUpdateExist");

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

QTEST_APPLESS_MAIN(UpdateControllerTest)

#include "tst_updatecontrollertest.moc"
