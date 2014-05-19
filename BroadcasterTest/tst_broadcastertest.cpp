#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../MediaPlayer/src/Common/Interfaces/ListEntry.h"
#include "../../../MediaPlayer/src/Common/ListEntryImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModel.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.h"
#include "../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterController.h"
#include "../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterControllerImpl.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequest.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequestImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerImpl.h"
#include "../UpdateController/RequestManagerConnectionFakeImpl.h"

class BroadcasterTest : public QObject
{
    Q_OBJECT
    
public:
    const int BROADCAST_LIST_COUNT = 4;
    const int ROLES_COUNT = 3;


public:
    BroadcasterTest();
    
protected slots:
    void onRequestFinished(QList<BroadcasterModelEntry> &broadcasters, RequestStatuses::Status status);

private Q_SLOTS:
    void testBroadcasterModel_Create();
    void testBroadcasterModel_GetModelData_SetModelData();

    void testBroadcasterModelView_Create();
    void testBroadcasterModelView_rowCount();
    void testBroadcasterModelView_columnCount();
    void testBroadcasterModelView_setBroadcasterModel_getBroadcasterModel();
    void testBroadcasterModelView_roleNames();
    void testBroadcasterModelView_getData();
    void testBroadcasterModelView_setSearchString();

    void testBroadcasterController_Create();
    void testBroadcasterController_updateBroadcasters();


    void testBroadcasterRequest_Create();
    void testBroadcasterRequest_performRequest_notSetArguments();
    void testBroadcasterRequest_performRequest_notSetArguments_data();
    void testBroadcasterRequest_performRequest();
    void testBroadcasterRequest_performRequest_noNetworkConnection();


    void testCase1();
    void testCase1_data();

private:
    RequestStatuses::Status _statusResult;
    QList<BroadcasterModelEntry> _broadcasters;
private:
    void fillModelData(QList<BroadcasterModelEntry> &data);

};

BroadcasterTest::BroadcasterTest()
{
}

void BroadcasterTest::onRequestFinished(QList<BroadcasterModelEntry> &broadcasters, RequestStatuses::Status status)
{
    _statusResult = status;
    _broadcasters = broadcasters;

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

void BroadcasterTest::testBroadcasterModelView_setSearchString()
{
    //GIVEN
    BroadcasterModelView modelView;

    QList<BroadcasterModelEntry> data;
    fillModelData(data);

    BroadcasterModel *model = new BroadcasterModelImpl();
    model->setModelData(data);

    modelView.setBroadcasterModel(model);

    bool testResult = true;

    //WHEN
    modelView.setSearchString("2");
    int countRow = modelView.rowCount();


    //EXPECTED
    QModelIndex indx = modelView.index(0, 0, QModelIndex());
    QString modelDataName = modelView.data(indx, BroadcasterModelView :: NameRole).toString();
    QCOMPARE(modelDataName, QString("name2"));

    QCOMPARE(countRow, 2);

    //GIVEN
    BroadcasterModelEntry entry;
    entry.setName("name22");
    entry.setUrl("url1");
    entry.setVersion("V1");
    data.append(entry);

    //WHEN
    model->setModelData(data);
    countRow = modelView.rowCount();


    //EXPECTED
    QCOMPARE(countRow, 3);

    indx = modelView.index(2, 0, QModelIndex());
    modelDataName = modelView.data(indx, BroadcasterModelView :: NameRole).toString();
    QCOMPARE(modelDataName, QString("name22"));

}

void BroadcasterTest::testBroadcasterController_Create()
{
    //when
    BroadcasterController *brodcastController = new BroadcasterControllerImpl();

    //expected
    QVERIFY2(brodcastController!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterController_updateBroadcasters()
{
    //GIVEN
    RequestManagerImpl *requestManager = new RequestManagerImpl();
    requestManager->setNetworkAccessManager(new QNetworkAccessManager());

    RequestManagerConnectionFakeImpl requestManagerConnection;
    requestManagerConnection.setError(false);
    requestManagerConnection.setData("{\"broadcasters\":[{\"name\":\"GoWeb\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"1.2\"},{\"name\":\"1GoWeb1\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"4.3\"},{\"name\":\"GoWeb_gg\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"2.2\"},{\"name\":\"Ytv\",\"url\":\"http:\/\/tvapi.ytv.su\/\",\"version\":\"1.2\"}]}");

    BroadcasterRequestImpl *request = new BroadcasterRequestImpl();
    request->setRequestManager(requestManager);
    request->setRequestManagerConnection(&requestManagerConnection);

    BroadcasterModelImpl *model = new BroadcasterModelImpl();

    BroadcasterControllerImpl brodcastControllerImpl;
    brodcastControllerImpl.setBroadcasterRequest(request);
    brodcastControllerImpl.setBroadcasterModel(model);
    BroadcasterController *brodcastController = &brodcastControllerImpl;


    //WHEN
    brodcastController->updateBroadcasters();


    //EXPECTED
    QCOMPARE(brodcastController->getStatus(), ControllerStatuses::Success);
    QCOMPARE(model->getModelData().count(),BROADCAST_LIST_COUNT);
}

void BroadcasterTest::testBroadcasterRequest_Create()
{
    //when
    BroadcasterRequest *brodcastRequest = new BroadcasterRequestImpl();

    //expected
    QVERIFY2(brodcastRequest!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterRequest_performRequest_notSetArguments()
{
    //given
    QFETCH(BroadcasterRequestImpl*, request);

    _statusResult = RequestStatuses::Success;
    QObject::connect(request, SIGNAL(requestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)),
                     this, SLOT(onRequestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)));

    //when
    request->performRequest();


    //expected
    QCOMPARE(_statusResult, RequestStatuses::ArgumentalError);
}

void BroadcasterTest::testBroadcasterRequest_performRequest_notSetArguments_data()
{
    QTest::addColumn<BroadcasterRequestImpl*>("request");

    BroadcasterRequestImpl *request = new BroadcasterRequestImpl();
    QTest::newRow("0") << request;

    RequestManagerImpl *requestManager = new RequestManagerImpl();
    RequestManagerConnectionImpl *requestManagerConnection = new RequestManagerConnectionImpl();

    request->setRequestManager(requestManager);

    QTest::newRow("1") << request;

    request->setRequestManagerConnection(requestManagerConnection);

    QTest::newRow("2") << request;

    request->setRequestManager(NULL);

    QTest::newRow("3") << request;

}

void BroadcasterTest::testBroadcasterRequest_performRequest()
{
    //GIVEN
    RequestManagerImpl *requestManager = new RequestManagerImpl();
    requestManager->setNetworkAccessManager(new QNetworkAccessManager());

    RequestManagerConnectionFakeImpl requestManagerConnection;
    requestManagerConnection.setError(false);
    requestManagerConnection.setData("{\"broadcasters\":[{\"name\":\"GoWeb\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"1.2\"},{\"name\":\"1GoWeb1\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"4.3\"},{\"name\":\"GoWeb_gg\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"2.2\"},{\"name\":\"Ytv\",\"url\":\"http:\/\/tvapi.ytv.su\/\",\"version\":\"1.2\"}]}");

    BroadcasterRequestImpl *request = new BroadcasterRequestImpl();
    request->setRequestManager(requestManager);
    request->setRequestManagerConnection(&requestManagerConnection);

    _statusResult = RequestStatuses::UnknownServerError;
    QObject::connect(request, SIGNAL(requestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)),
                     this, SLOT(onRequestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)));

    //when
    request->performRequest();


    //expected
    QCOMPARE(_statusResult, RequestStatuses::Success);
    QCOMPARE(_broadcasters.count(),BROADCAST_LIST_COUNT);

}

void BroadcasterTest::testBroadcasterRequest_performRequest_noNetworkConnection()
{
    RequestManagerImpl *requestManager = new RequestManagerImpl();
    requestManager->setNetworkAccessManager(new QNetworkAccessManager());

    RequestManagerConnectionFakeImpl requestManagerConnection;
    requestManagerConnection.setError(true);

    BroadcasterRequestImpl *request = new BroadcasterRequestImpl();
    request->setRequestManager(requestManager);
    request->setRequestManagerConnection(&requestManagerConnection);

    _statusResult = RequestStatuses::Success;
    QObject::connect(request, SIGNAL(requestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)),
                     this, SLOT(onRequestFinished(QList<BroadcasterModelEntry> &, RequestStatuses::Status)));

    //when
    request->performRequest();


    //expected
    QCOMPARE(_statusResult, RequestStatuses::NetworkFailure);
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
    entry.setName("2name3");
    entry.setUrl("url3");
    entry.setVersion("V3");
    data.append(entry);
    entry.setName("name4");
    entry.setUrl("url4");
    entry.setVersion("V4");
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
