#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.h>
#include <../../../MediaPlayer/src/Controllers/Files/TVFileController.h>
#include <../../../MediaPlayer/src/Controllers/Files/AbstractTVFileController.h>
#include <../../../MediaPlayer/src/DB/AbstractDBConnector.h>
#include <../../../MediaPlayer/src/DB/DBConnector.h>


class FakeDBConnector : public AbstractDBConnector
{

public:
    FakeDBConnector(){}

};


class TVFileControllerTest : public QObject
{
    Q_OBJECT
    
public:
    TVFileControllerTest();
    
private Q_SLOTS:
    void createTVFileControllerTest();
    void setDbConnectorTest();
    void notSetDbConnectorTest();
    void setTvGidSqlModelTest();
    void notSetTvGidSqlModelTest();
    void initTvFileControllerTest();
    void initTvFileController_NoDbConnector_Test();
};

TVFileControllerTest::TVFileControllerTest()
{
}

void TVFileControllerTest::createTVFileControllerTest()
{
    //Given
    //When

    TVFileController *tvFileController = new TVFileController();

    //Expected
    QVERIFY2(tvFileController!=NULL, "Failure create tvFileController");
}

void TVFileControllerTest::setDbConnectorTest()
{
    //Given
    TVFileController tvFileController;
    FakeDBConnector dbConnector;

    //When
    tvFileController.setDbConnector(&dbConnector);


    //Expected
    QVERIFY2(tvFileController.dbConnector() == &dbConnector, "Failure setDbConnector");

}

void TVFileControllerTest::notSetDbConnectorTest()
{
    //Given
    TVFileController tvFileController;

    //When

    //Expected
    QVERIFY2(tvFileController.dbConnector() == NULL, "Failure DbConnector after init must be NULL ");
}

void TVFileControllerTest::setTvGidSqlModelTest()
{
    //Given
    TVFileController tvFileController;
    TVGidSqlModel model;

    //When
    tvFileController.setTvGidSqlModel(&model);


    //Expected
    QVERIFY2(tvFileController.tvGidSqlModel()==&model, "Failure setTvGidSqlModel");
}

void TVFileControllerTest::notSetTvGidSqlModelTest()
{
    //Given
    TVFileController tvFileController;
    FakeDBConnector dbConnector;

    //When
    tvFileController.setDbConnector(&dbConnector);


    //Expected
    QVERIFY2(tvFileController.dbConnector() == &dbConnector, "Failure setDbConnector");

}

void TVFileControllerTest::initTvFileControllerTest()
{
    //Given
    TVFileController *tvFileController = new TVFileController();
    TVGidSqlModel model;
    DBConnector dbConnector;
    tvFileController->setTvGidSqlModel(&model);
    tvFileController->setDbConnector(&dbConnector);

    //When
    bool isInitOk = tvFileController->initTvFileController();

    //Expected
    QVERIFY2(isInitOk, "Failure init");
}

void TVFileControllerTest::initTvFileController_NoDbConnector_Test()
{
    //Given
    TVFileController *tvFileController = new TVFileController();
    TVGidSqlModel model;
    tvFileController->setTvGidSqlModel(&model);


    //When
    bool isInitOk = tvFileController->initTvFileController();

    //Expected
    QVERIFY2(isInitOk == false, "Failure checking incorrect DbConnector");
}


QTEST_APPLESS_MAIN(TVFileControllerTest)

#include "tst_tvfilecontrollertest.moc"
