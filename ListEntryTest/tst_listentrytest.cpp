#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Common/Interfaces/ListEntry.h"
#include "../../../MediaPlayer/src/Common/ListEntryImpl.h"

class ListEntryTest : public QObject
{
    Q_OBJECT
    
public:
    ListEntryTest();
    
private Q_SLOTS:
    void testCreateListQString();
    void test_Append_Size_At();
    void test_Clear_Replace();

    void testCase1();
    void testCase1_data();
};

ListEntryTest::ListEntryTest()
{
}

void ListEntryTest::testCreateListQString()
{
    //when
    ListEntry<QString> *list = new ListEntryImpl<QString>();
    //Expected
    QVERIFY2(list!=NULL, "Failure create");
}

void ListEntryTest::test_Append_Size_At()
{
    //Given
    ListEntry<QString> *list = new ListEntryImpl<QString>();
    //when
    list->append("123");
    int size = list->size();
    QString s = list->at(0);

    //expected
    QCOMPARE(size,1);
    QCOMPARE(s,QString("123"));
}

void ListEntryTest::test_Clear_Replace()
{
    //Given
    ListEntry<QString> *list = new ListEntryImpl<QString>();
    list->append("123");

    //when
    list->replace(0,"111");
    int size = list->size();
    QString s = list->at(0);

    list->clear();
    int sizeClr = list->size();

    //expected
    QCOMPARE(size,1);
    QCOMPARE(s,QString("111"));
    QCOMPARE(sizeClr,0);
}

void ListEntryTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void ListEntryTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(ListEntryTest)

#include "tst_listentrytest.moc"
