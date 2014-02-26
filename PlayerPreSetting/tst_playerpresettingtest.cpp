#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Common/Interfaces/PreSettingVisitor.h"
#include "../../../MediaPlayer/src/Controls/VLCPlayer/PlayerPreSettable.h"
#include "../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitorImpl.h"
#include "../../../MediaPlayer/src/Data/Settings.h"
#include "PlayerPreSettableFakeImpl.h"

class PlayerPreSettingTest : public QObject
{
    Q_OBJECT
    
public:
    PlayerPreSettingTest();
    
private Q_SLOTS:
    void testDefineInterface();
    void testSetSettings();
    void test_loadSettings_noObjectForVisit();
    void test_loadSettings_byDefaulte();
    void test_loadSettings_noSettings();
    void test_saveSettings();
};

PlayerPreSettingTest::PlayerPreSettingTest()
{
}

void PlayerPreSettingTest::testDefineInterface()
{

    //WHEN
    PlayerPreSettable *playerPreSettable;
    PreSettingVisitor *preSettingVisitor = new PreSettingVisitorImpl(playerPreSettable);

    //EXPEXTED
    QVERIFY2(preSettingVisitor!=NULL, "Init failure");
}

void PlayerPreSettingTest::testSetSettings()
{

    //Given
    PlayerPreSettable *playerPreSettable;
    PreSettingVisitorImpl *preSettingVisitorImpl = new PreSettingVisitorImpl(playerPreSettable);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = preSettingVisitorImpl;

    //when
    preSettingVisitor->setSettings(settings);

    //expected
    QCOMPARE(settings,preSettingVisitorImpl->settings());
}

void PlayerPreSettingTest::test_loadSettings_noObjectForVisit()
{

    //Given
    PreSettingVisitorImpl *preSettingVisitorImpl = new PreSettingVisitorImpl(NULL);
    PreSettingVisitor *preSettingVisitor = preSettingVisitorImpl;

    Settings *settings = Settings::sharedInstance();
    preSettingVisitor->setSettings(settings);

    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected
    QCOMPARE(status, PreSettingVisitor::IllgalArgument);
}

void PlayerPreSettingTest::test_loadSettings_noSettings()
{

    //Given
    PlayerPreSettable *playerPreSettable = new PlayerPreSettableFakeImpl();
    PreSettingVisitorImpl *preSettingVisitorImpl = new PreSettingVisitorImpl(playerPreSettable);
    PreSettingVisitor *preSettingVisitor = preSettingVisitorImpl;

    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected
    QCOMPARE(status, PreSettingVisitor::IllgalArgument);
}

void PlayerPreSettingTest::test_loadSettings_byDefaulte()
{

    //Given
    PlayerPreSettableFakeImpl playerPreSettableImpl;
    playerPreSettableImpl.setMuted(true);
    playerPreSettableImpl.setVolume(0);
    PlayerPreSettable *playerPreSettable = &playerPreSettableImpl;
    PreSettingVisitorImpl *preSettingVisitorImpl = new PreSettingVisitorImpl(playerPreSettable);
    PreSettingVisitor *preSettingVisitor = preSettingVisitorImpl;

    Settings *settings = Settings::sharedInstance();
    preSettingVisitor->setSettings(settings);
    settings->setVolume(1);
    settings->setMuted(false);

    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected
    QCOMPARE(status, PreSettingVisitor::Success);
    QCOMPARE(playerPreSettableImpl.muted(), false);
    QCOMPARE(playerPreSettableImpl.volume(), 1.0);
}


void PlayerPreSettingTest::test_saveSettings()
{

    //Given
    PlayerPreSettableFakeImpl playerPreSettableImpl;
    PlayerPreSettable *playerPreSettable = &playerPreSettableImpl;
    PreSettingVisitorImpl *preSettingVisitorImpl = new PreSettingVisitorImpl(playerPreSettable);
    PreSettingVisitor *preSettingVisitor = preSettingVisitorImpl;

    Settings *settings = Settings::sharedInstance();
    preSettingVisitor->setSettings(settings);

    //when
    playerPreSettableImpl.setMuted(true);
    playerPreSettableImpl.setVolume(0.2);
    preSettingVisitor->saveSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();
    playerPreSettableImpl.setMuted(false);
    playerPreSettableImpl.setVolume(0);
    preSettingVisitor->loadSettings();


    //expected
    QCOMPARE(status, PreSettingVisitor::Success);
    QCOMPARE(playerPreSettableImpl.muted(), true);
    QCOMPARE(playerPreSettableImpl.volume(), (float)0.2);
}

QTEST_APPLESS_MAIN(PlayerPreSettingTest)

#include "tst_playerpresettingtest.moc"
