#include <QString>
#include <QtTest>

class PreviewPlaylistControllerTest : public QObject
{
    Q_OBJECT
    
public:
    PreviewPlaylistControllerTest();
    
private Q_SLOTS:
    void testCase1();
};

PreviewPlaylistControllerTest::PreviewPlaylistControllerTest()
{
}

void PreviewPlaylistControllerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PreviewPlaylistControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
