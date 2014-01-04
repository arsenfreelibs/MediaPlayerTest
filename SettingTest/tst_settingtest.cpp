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
    void testGetDefPath();
    void testGetPath();

private:
    QString createLogoFile();

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

void SettingTest::testGetDefPath()
{
    //Given
    Settings *settings = Settings::sharedInstance();
    QSettings qsettings(QSettings::IniFormat,
                    QSettings::UserScope,
                    QCoreApplication::organizationName(),
                    QCoreApplication::applicationName()
                    );
    //when
    QString path = settings->pathToLogoFile();

    //expected
    QCOMPARE(path,Settings::DEFAUL_PATH);

}

void SettingTest::testGetPath()
{
    //Given
    Settings *settings = Settings::sharedInstance();
    QString pathToFakeLogo = createLogoFile();
    settings->setLanguage("ru"); //TODO: need for creation .ini file


    //when
    QString path = settings->pathToLogoFile();

    //expected
    QCOMPARE(path,pathToFakeLogo);
}

QString SettingTest::createLogoFile()
{
    QSettings qsettings(QSettings::IniFormat,
                    QSettings::UserScope,
                    QCoreApplication::organizationName(),
                    QCoreApplication::applicationName()
                    );
    QFileInfo fileInfo(qsettings.fileName());
    QString logoFileName = fileInfo.absolutePath() + "//logo.gif";
    QFile logoFile(logoFileName);
    if (!logoFile.open(QIODevice::WriteOnly)) {
        return "Cann't create fake logo file";
    }
    logoFile.write("123");
    logoFile.close();
    return fileInfo.absolutePath();
}

QTEST_MAIN(SettingTest)

#include "tst_settingtest.moc"
