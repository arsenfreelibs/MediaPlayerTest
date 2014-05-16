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
    const int BROADCAST_LIST_COUNT = 2;
    const int ROLES_COUNT = 3;


public:
    BroadcasterTest();
    
private Q_SLOTS:
    void testBroadcasterModel_Create();
    void testBroadcasterModel_GetModelData_SetModelData();

    void testBroadcasterModelView_Create();
    void testBroadcasterModelView_rowCount();
    void testBroadcasterModelView_columnCount();
    void testBroadcasterModelView_setBroadcasterModel_getBroadcasterModel();
    void testBroadcasterModelView_roleNames();
    void testBroadcasterModelView_getData();


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
    QVERIFY2(data.count() == BROADCAST_LIST_COUNT, "Failure");
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

void BroadcasterTest::testBroadcasterModelView_rowCount()
{
    //Given
    QList<BroadcasterModelEntry> data;
    fillModelData(data);

    BroadcasterModel *model = new BroadcasterModelImpl();
    model->setModelData(data);

    BroadcasterModelView modelViewImpl;
    modelViewImpl.setBroadcasterModel(model);

    QAbstractListModel *modelView = &modelViewImpl;

    //When
    int rowCount = modelView->rowCount();

    //Expected
    QVERIFY2(rowCount==BROADCAST_LIST_COUNT, "Failure");
}

void BroadcasterTest::testBroadcasterModelView_columnCount()
{
    //Given
    BroadcasterModelView *modelView = new BroadcasterModelView();

    //when
    int column = modelView->columnCount();
    //expexted
    QVERIFY2(column == 1, "Failure");
}

void BroadcasterTest::testBroadcasterModelView_setBroadcasterModel_getBroadcasterModel()
{
    //Given
    BroadcasterModelView modelView;

    QList<BroadcasterModelEntry> data;
    fillModelData(data);

    BroadcasterModel *model = new BroadcasterModelImpl();
    model->setModelData(data);

    //When
    modelView.setBroadcasterModel(model);
    BroadcasterModel *modelGet = modelView.getBroadcasterModel();

    //Expected
    QVERIFY2(model==modelGet, "Failure");
}

void BroadcasterTest::testBroadcasterModelView_roleNames()
{
    //GIVEN
    BroadcasterModelView modelView;
    QHash<int,QByteArray> roles;

    //WHEN
    roles = modelView.roleNames();

    //EXPECTED
    QByteArray name = roles.value(BroadcasterModelView :: NameRole);
    QByteArray url = roles.value(BroadcasterModelView :: UrlRole);
    QByteArray version = roles.value(BroadcasterModelView :: VersionRole);

    int base_role_count = 6;
    QCOMPARE(roles.count(),ROLES_COUNT+base_role_count);

    QCOMPARE(name, QByteArray("name"));
    QCOMPARE(url, QByteArray("url"));
    QCOMPARE(version, QByteArray("version"));
}

void BroadcasterTest::testBroadcasterModelView_getData()
{
    //GIVEN
    BroadcasterModelView modelView;

    QList<BroadcasterModelEntry> data;
    fillModelData(data);

    BroadcasterModel *model = new BroadcasterModelImpl();
    model->setModelData(data);

    modelView.setBroadcasterModel(model);

    int countRow = modelView.rowCount();
    QModelIndex indx = modelView.index(0, 0, QModelIndex());
    bool testResult = true;


    //WHEN
    for (int i = 0; i < countRow; i++)
    {
        indx = modelView.index(i, 0, QModelIndex());
        QString modelDataName = modelView.data(indx, BroadcasterModelView :: NameRole).toString();
        if (modelDataName != data.at(i).name())
        {
             testResult = false;
        }

        QString modelDataUrl = modelView.data(indx, BroadcasterModelView :: UrlRole).toString();
        if (modelDataUrl != data.at(i).url())
        {
             testResult = false;
        }

        QString modelDataVer = modelView.data(indx, BroadcasterModelView :: VersionRole).toString();
        if (modelDataVer != data.at(i).version())
        {
             testResult = false;
        }
    }

    //EXPECTED
    QVERIFY2(testResult, "Failure");
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
