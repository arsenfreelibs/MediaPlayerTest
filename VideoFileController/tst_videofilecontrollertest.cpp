#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Controllers/Files/AbstractVideoFileController.h>
#include <../../../MediaPlayer/src/Controllers/Files/VideoFileController.h>
#include <../../../MediaPlayer/src/Data/SqlModels/VideoSqlTableModel.h>

class VideoFileControllerTest : public QObject
{
    Q_OBJECT
    
public:
    VideoFileControllerTest();
    
private Q_SLOTS:
    void testCreateAbstractVideoFileController();
    void testCreateVideoFileController();

    void test_SaveDownloadedVideoData_VideoFileController();

    void test_create_VideoSqlTableModel();
};

VideoFileControllerTest::VideoFileControllerTest()
{
}

void VideoFileControllerTest::testCreateAbstractVideoFileController()
{
    //given

    //when
    AbstractVideoFileController abstractVideoFileController;

    //expexted
    QVERIFY2(true, "");
}

void VideoFileControllerTest::testCreateVideoFileController()
{
    //given

    //when
    VideoFileController abstractVideoFileController;

    //expexted
    QVERIFY2(true, "");
}

void VideoFileControllerTest::test_SaveDownloadedVideoData_VideoFileController()
{
    //given
    VideoFileController videoFileController;
    MovieItemDataAccess item;

    //when
    bool result = videoFileController.SaveDownloadedVideoData(item, "");


    //expexted
    QVERIFY2(result, "Fail saving video data");
}

void VideoFileControllerTest::test_create_VideoSqlTableModel()
{
    //given

    //when
    VideoSqlTableModel model;

    //expected
    QVERIFY2(true, "");

}

QTEST_APPLESS_MAIN(VideoFileControllerTest)

#include "tst_videofilecontrollertest.moc"
