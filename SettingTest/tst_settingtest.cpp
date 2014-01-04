#include <QString>
#include <QtTest>
#include <QCoreApplication>

class SettingTest : public QObject
{
    Q_OBJECT
    
public:
    SettingTest();
    
private Q_SLOTS:
    void testInitClass();
};

SettingTest::SettingTest()
{
}

void SettingTest::testInitClass()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(SettingTest)

#include "tst_settingtest.moc"
