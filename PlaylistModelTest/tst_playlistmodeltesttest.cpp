#include <QString>
#include <QtTest>

class PlaylistModelTestTest : public QObject
{
    Q_OBJECT
    
public:
    PlaylistModelTestTest();
    
private Q_SLOTS:
    void testCase1();
};

PlaylistModelTestTest::PlaylistModelTestTest()
{
}

void PlaylistModelTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PlaylistModelTestTest)

#include "tst_playlistmodeltesttest.moc"
