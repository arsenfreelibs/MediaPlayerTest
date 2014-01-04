#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../MediaPlayer/src/Data/Settings.h"

class SettingTest : public QObject
{
    Q_OBJECT
    
public:
    SettingTest();
    
private Q_SLOTS:
    void testInitClass();
    void testInitValues();
    void testGetPath();

};

SettingTest::SettingTest()
{
}

void SettingTest::testInitClass()
{
    Settings *settings = Settings::sharedInstance();
    QVERIFY2(settings!=NULL, "Init failure");
}

void SettingTest::testInitValues()
{
    Settings *settings = Settings::sharedInstance();
    //TODO: need del .ini file befor exec this test
}

void SettingTest::testGetPath()
{
    //Given
    Settings *settings = Settings::sharedInstance();
    QSettings qsettings(QSettings::IniFormat,
                    QSettings::UserScope,
                    QCoreApplication::organizationName(),
                    QCoreApplication::applicationName()
                    );
    //when
    QString path = settings->path();

    //expected
    QCOMPARE(path+"/tst_settingtest.ini",qsettings.fileName());
}

QTEST_MAIN(SettingTest)

#include "tst_settingtest.moc"
