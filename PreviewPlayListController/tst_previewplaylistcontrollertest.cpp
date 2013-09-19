#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.h>

class PreviewPlayListControllerTest : public QObject
{
    Q_OBJECT

private:
    PreviewPlaylistController h;

public:
    PreviewPlayListControllerTest();
    
private Q_SLOTS:
    void testCase1();
};

PreviewPlayListControllerTest::PreviewPlayListControllerTest()
{
}

void PreviewPlayListControllerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PreviewPlayListControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
