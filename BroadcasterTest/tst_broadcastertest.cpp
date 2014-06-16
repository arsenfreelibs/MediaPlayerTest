#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../MediaPlayer/src/Common/Interfaces/ListEntry.h"
#include "../../../MediaPlayer/src/Common/ListEntryImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModel.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelInfo.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelInfoImpl.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterInfoModelView.h"
#include "../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.h"
#include "../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterController.h"
#include "../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterControllerImpl.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequest.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequestImpl.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterInfoRequest.h"
#include "../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterInfoRequestImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerImpl.h"
#include "../UpdateController/RequestManagerConnectionFakeImpl.h"

class BroadcasterTest : public QObject
{
    Q_OBJECT
    
public:
    const int BROADCAST_LIST_COUNT = 4;
    const int ROLES_COUNT = 3;
    const int BROADCAST_CHANEL_LIST_COUNT = 4;
    const int BROADCAST_PACKET_LIST_COUNT = 2;


public:
    BroadcasterTest();
    
protected slots:
    void onRequestFinished(QList<BroadcasterModelEntry> &broadcasters, RequestStatuses::Status status);
    void onRequestInfoFinished(BroadcasterInfo &broadcasterInfo, RequestStatuses::Status status);

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
    void testBroadcasterController_getBroadcasterInfo();


    void testBroadcasterRequest_Create();
    void testBroadcasterRequest_performRequest_notSetArguments();
    void testBroadcasterRequest_performRequest_notSetArguments_data();
    void testBroadcasterRequest_performRequest();
    void testBroadcasterRequest_performRequest_noNetworkConnection();

    void testBroadcasterModelInfo_create();

    void testBroadcasterInfoModelView_create();

    void testBroadcasterInfoRequest_create();
    void testBroadcasterInfoRequest_performRequest_notSetArguments();
    void testBroadcasterInfoRequest_performRequest_notSetArguments_data();
    void testBroadcasterInfoRequest_performRequest();



    void testCase1();
    void testCase1_data();

private:
    RequestStatuses::Status _statusResult;
    QList<BroadcasterModelEntry> _broadcasters;
    BroadcasterInfo _broadcasterInfo;

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

void BroadcasterTest::onRequestInfoFinished(BroadcasterInfo &broadcasterInfo, RequestStatuses::Status status)
{
    _statusResult = status;
    _broadcasterInfo = broadcasterInfo;

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

void BroadcasterTest::testBroadcasterController_getBroadcasterInfo()
{
    //GIVEN
    RequestManagerImpl *requestManager = new RequestManagerImpl();
    requestManager->setNetworkAccessManager(new QNetworkAccessManager());

    RequestManagerConnectionFakeImpl requestManagerConnection;
    requestManagerConnection.setError(false);
    requestManagerConnection.setData("{\"broadcasters\":[{\"name\":\"GoWeb\",\"url\":\"https:\/\/tvapi.goweb.com\",\"version\":\"1.2\"},{\"name\":\"1GoWeb1\",\"url\":\"https:\/\/tvapi.goweb.com\",\"version\":\"4.3\"},{\"name\":\"GoWeb_gg\",\"url\":\"https:\/\/tvapi.goweb.com\/\",\"version\":\"2.2\"},{\"name\":\"Ytv\",\"url\":\"http:\/\/tvapi.ytv.su\/\",\"version\":\"1.2\"}]}");

    BroadcasterRequestImpl *request = new BroadcasterRequestImpl();
    request->setRequestManager(requestManager);
    request->setRequestManagerConnection(&requestManagerConnection);

    RequestManagerConnectionFakeImpl requestManagerConnectionInfo;
    requestManagerConnectionInfo.setError(false);
    requestManagerConnectionInfo.setData("{\"error\":0,\"packets\":[{\"id\":9,\"name\":\"Home\",\"cost\":\"0.99\",\"type\":\"BASE\",\"channels\":[1,2,3,4,5]},{\"id\":6,\"name\":\"\u0420\u0435\u043a\u043b\u0430\u043c\u043d\u0438\u0439\",\"cost\":\"0\",\"type\":\"BASE\",\"channels\":[2,3,5]}],\"channels\":[{\"id\":1,\"name\":\"Zero\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/zero.png\"},{\"id\":2,\"name\":\"GO\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/go.png\"},{\"id\":3,\"name\":\"GOodwin\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/goodwin.png\"},{\"id\":4,\"name\":\"\u0410\u0439\u0440\u0438\u043d\u0430\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/airina.png\"},{\"id\":5,\"name\":\"SIRIUS\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/sirius.png\"},{\"id\":6,\"name\":\"\u0414\u0435\u0442\u0441\u043a\u0438\u0439 \u043c\u0438\u0440\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/detskyimir.png\"},{\"id\":7,\"name\":\"\u041c\u0430\u0442\u044c \u0438 \u0434\u0438\u0442\u044f\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/matiditia.png\"},{\"id\":8,\"name\":\"\u041a\u0430\u0440\u0443\u0441\u0435\u043b\u044c\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/karusel.png\"},{\"id\":9,\"name\":\"\u0414\u0435\u0442\u0441\u043a\u0438\u0439\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/detskii.png\"}],\"time\":1402835394}");
    requestManagerConnectionInfo.setUrlStr("https://tvapi.goweb.com/1.2/services");

    BroadcasterInfoRequestImpl *requestInfo = new BroadcasterInfoRequestImpl();
    requestInfo->setRequestManager(requestManager);
    requestInfo->setRequestManagerConnection(&requestManagerConnectionInfo);


    BroadcasterModelImpl *model = new BroadcasterModelImpl();

    BroadcasterModelInfoImpl *modelInfo = new BroadcasterModelInfoImpl();

    BroadcasterControllerImpl brodcastControllerImpl;
    brodcastControllerImpl.setBroadcasterRequest(request);
    brodcastControllerImpl.setBroadcasterModel(model);
    brodcastControllerImpl.setBroadcasterInfoRequest(requestInfo);
    brodcastControllerImpl.setBroadcasterModelInfo(modelInfo);

    BroadcasterController *brodcastController = &brodcastControllerImpl;

    BroadcasterInfoModelView infoModelView;
    infoModelView.setBroadcasterModel(modelInfo);

    brodcastController->updateBroadcasters();

    //WHEN
    brodcastController->getBroadcasterInfo(0);

    //EXPECTED
    QCOMPARE(brodcastController->getStatus(), ControllerStatuses::Success);
    QCOMPARE(modelInfo->getModelData()._packets.count() ,BROADCAST_PACKET_LIST_COUNT);

    //WHEN
    QModelIndex indx = infoModelView.index(0, 0, QModelIndex());
    QString modelDataName = infoModelView.data(indx, BroadcasterModelView :: NameRole).toString();

    //EXPECTED
    QCOMPARE(modelDataName, QString("Home"));
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

void BroadcasterTest::testBroadcasterModelInfo_create()
{
    //when
    BroadcasterModelInfo *broadcaster = new BroadcasterModelInfoImpl();

    //expected
    QVERIFY2(broadcaster!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterInfoModelView_create()
{
    //when
    BroadcasterInfoModelView *broadcaster = new BroadcasterInfoModelView();

    //expected
    QVERIFY2(broadcaster!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterInfoRequest_create()
{

    //when
    BroadcasterInfoRequest *request = new BroadcasterInfoRequestImpl();

    //expected
    QVERIFY2(request!=NULL, "Failure create");
}

void BroadcasterTest::testBroadcasterInfoRequest_performRequest_notSetArguments()
{
    //given
    QFETCH(BroadcasterInfoRequestImpl*, request);

    _statusResult = RequestStatuses::Success;
    QObject::connect(request, SIGNAL(requestFinished(BroadcasterInfo &, RequestStatuses::Status)),
                     this, SLOT(onRequestInfoFinished(BroadcasterInfo &, RequestStatuses::Status)));

    //when
    request->performRequest("");


    //expected
    QCOMPARE(_statusResult, RequestStatuses::ArgumentalError);
}

void BroadcasterTest::testBroadcasterInfoRequest_performRequest_notSetArguments_data()
{
    QTest::addColumn<BroadcasterInfoRequestImpl*>("request");

    BroadcasterInfoRequestImpl *request = new BroadcasterInfoRequestImpl();
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

void BroadcasterTest::testBroadcasterInfoRequest_performRequest()
{
    //GIVEN
    RequestManagerImpl *requestManager = new RequestManagerImpl();
    requestManager->setNetworkAccessManager(new QNetworkAccessManager());

    RequestManagerConnectionFakeImpl requestManagerConnection;
    requestManagerConnection.setError(false);
    requestManagerConnection.setData("{\"error\":0,\"packets\":[{\"id\":9,\"name\":\"home\",\"cost\":\"0.99\",\"type\":\"BASE\",\"channels\":[1,2,3,4,5]},{\"id\":6,\"name\":\"\u0420\u0435\u043a\u043b\u0430\u043c\u043d\u0438\u0439\",\"cost\":\"0\",\"type\":\"BASE\",\"channels\":[2,3,5]}],\"channels\":[{\"id\":1,\"name\":\"Zero\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/zero.png\"},{\"id\":2,\"name\":\"GO\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/go.png\"},{\"id\":3,\"name\":\"GOodwin\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/goodwin.png\"},{\"id\":4,\"name\":\"\u0410\u0439\u0440\u0438\u043d\u0430\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/airina.png\"},{\"id\":5,\"name\":\"SIRIUS\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/sirius.png\"},{\"id\":6,\"name\":\"\u0414\u0435\u0442\u0441\u043a\u0438\u0439 \u043c\u0438\u0440\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/detskyimir.png\"},{\"id\":7,\"name\":\"\u041c\u0430\u0442\u044c \u0438 \u0434\u0438\u0442\u044f\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/matiditia.png\"},{\"id\":8,\"name\":\"\u041a\u0430\u0440\u0443\u0441\u0435\u043b\u044c\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/karusel.png\"},{\"id\":9,\"name\":\"\u0414\u0435\u0442\u0441\u043a\u0438\u0439\",\"logo\":\"http:\/\/goods.ytv.su\/logos\/68x48\/detskii.png\"}],\"time\":1402835394}");

    BroadcasterInfoRequestImpl *request = new BroadcasterInfoRequestImpl();
    request->setRequestManager(requestManager);
    request->setRequestManagerConnection(&requestManagerConnection);

    _statusResult = RequestStatuses::Success;
    QObject::connect(request, SIGNAL(requestFinished(BroadcasterInfo &, RequestStatuses::Status)),
                     this, SLOT(onRequestInfoFinished(BroadcasterInfo &, RequestStatuses::Status)));

    //when
    request->performRequest("http://tvapi.ytv.su/1.2/services");


    //expected
    QCOMPARE(_statusResult, RequestStatuses::Success);
    QCOMPARE(_broadcasterInfo._packets.count(),BROADCAST_PACKET_LIST_COUNT);
    QCOMPARE(_broadcasterInfo._chanals.count(),BROADCAST_CHANEL_LIST_COUNT);

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
