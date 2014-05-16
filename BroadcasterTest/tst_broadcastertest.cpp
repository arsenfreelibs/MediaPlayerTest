#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../MediaPlayer/src/Common/Interfaces/ListEntry.h"
#include "../../../MediaPlayer/src/Common/ListEntryImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModel.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.h"

class BroadcasterTest : public QObject
{
    Q_OBJECT
    
public:
    BroadcasterTest();
    
private Q_SLOTS:
    void testBroadcasterModel_Create();
    void testBroadcasterModel_GetModelData_SetModelData();

    void testBroadcasterModelView_Create();



    void testCase1();
    void testCase1_data();

private:
    void fillModelData(QList<BroadcasterModelEntry> &data);

};

BroadcasterTest::BroadcasterTest()
{
}

void BroadcasterTest::testBroadcasterModel_Create()
{
    //when
    BroadcasterModel *model = new BroadcasterModelImpl();

    //expected
    QVERIFY2(model!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterModel_GetModelData_SetModelData()
{
    //Given
    BroadcasterModel *model = new BroadcasterModelImpl();

    QList<BroadcasterModelEntry> data;
    fillModelData(data);

    //when
    model->setModelData(data);
    QList<BroadcasterModelEntry> getData = model->getModelData();


    //expected
    QVERIFY2(data.count() == 2, "Failure");
    QVERIFY2(data.count() == getData.count(), "Failure");
    QVERIFY2(data.at(0).name() == getData.at(0).name(), "Failure");
}

void BroadcasterTest::testBroadcasterModelView_Create()
{
    //when
    QAbstractListModel *modelView = new BroadcasterModelView();

    //expected
    QVERIFY2(modelView!=NULL, "Failure create");

}

void BroadcasterTest::fillModelData(QList<BroadcasterModelEntry> &data)
{
    BroadcasterModelEntry entry;
    entry.setName("name1");
    entry.setUrl("url1");
    entry.setVersion("V1");
    data.append(entry);
    entry.setName("name2");
    entry.setUrl("url2");
    entry.setVersion("V2");
    data.append(entry);
}

void BroadcasterTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void BroadcasterTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(BroadcasterTest)

#include "tst_broadcastertest.moc"
