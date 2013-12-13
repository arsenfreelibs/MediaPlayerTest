#include <QString>
#include <QtTest>

class AdvertisementTest : public QObject
{
    Q_OBJECT
    
public:
    AdvertisementTest();
    
private Q_SLOTS:
    void testCase1();
};

AdvertisementTest::AdvertisementTest()
{
}

void AdvertisementTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(AdvertisementTest)

#include "tst_advertisementtest.moc"
