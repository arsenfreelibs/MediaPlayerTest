#include <QString>
#include <QtTest>

class UpdateControllerTest : public QObject
{
    Q_OBJECT
    
public:
    UpdateControllerTest();
    
private Q_SLOTS:
    void testInterfaceAvailible();
};

UpdateControllerTest::UpdateControllerTest()
{
}

void UpdateControllerTest::testInterfaceAvailible()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UpdateControllerTest)

#include "tst_updatecontrollertest.moc"
