#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp"

class PreviewPlaylistControllerTest : public QObject
{
    Q_OBJECT
    
public:
    PreviewPlaylistControllerTest();
    
private Q_SLOTS:
    void test_createPreviewPlaylistController();
};

PreviewPlaylistControllerTest::PreviewPlaylistControllerTest()
{
}

void PreviewPlaylistControllerTest::test_createPreviewPlaylistController()
{
    PreviewPlaylistController *previewPlaylistController = new PreviewPlaylistController();
    QVERIFY2(previewPlaylistController != NULL, "Failure");
}

QTEST_APPLESS_MAIN(PreviewPlaylistControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
