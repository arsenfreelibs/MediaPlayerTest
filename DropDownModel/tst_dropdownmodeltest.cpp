#include <QString>
#include <QtTest>

class DropDownModelTest : public QObject
{
    Q_OBJECT
    
public:
    DropDownModelTest();
    
private Q_SLOTS:
    void testCase1();
};

DropDownModelTest::DropDownModelTest()
{
}

void DropDownModelTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(DropDownModelTest)

#include "tst_dropdownmodeltest.moc"
