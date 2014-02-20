#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitor.h"
#include "../../../MediaPlayer/src/Controls/VLCPlayer/PlayerPreSettable.h"
#include "../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitorImpl.h"
#include "../../../MediaPlayer/src/Data/Settings.h"

class PlayerPreSettingTest : public QObject
{
    Q_OBJECT
    
public:
    PlayerPreSettingTest();
    
private Q_SLOTS:
    void testDefineInterface();
    void testSetSettings();
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
    QVERIFY2(settings!=preSettingVisitorImpl->settings(), "se settings failure");
}

QTEST_APPLESS_MAIN(PlayerPreSettingTest)

#include "tst_playerpresettingtest.moc"
