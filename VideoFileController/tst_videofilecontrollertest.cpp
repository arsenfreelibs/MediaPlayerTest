#include <QString>
#include <QtTest>

class VideoFileControllerTest : public QObject
{
    Q_OBJECT
    
public:
    VideoFileControllerTest();
    
private Q_SLOTS:
    void testCreateAbstractVideoFileController();
};

VideoFileControllerTest::VideoFileControllerTest()
{
}

void VideoFileControllerTest::testCreateAbstractVideoFileController()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VideoFileControllerTest)

#include "tst_videofilecontrollertest.moc"
