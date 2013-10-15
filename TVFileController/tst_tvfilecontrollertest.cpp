#include <QString>
#include <QtTest>
#include <QtSql>
#include <QSqlQueryModel>
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
    void setTvGidSqlModelTest();
    void notSetTvGidSqlModelTest();
    void initTvFileController_NoDbConnector_Test();
    void initTvFileControllerTest();


private:
    bool connectToSQL_DB();
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

    //When    


    //Expected
    QVERIFY2(tvFileController.tvGidSqlModel() == NULL, "Failure model mast be NULL");

}

void TVFileControllerTest::initTvFileControllerTest()
{
    //Given

    DBConnector dbConnector;
    dbConnector.setDbName(":memory:");
    dbConnector.connectToSqlDB();

    TVFileController *tvFileController = new TVFileController();
    TVGidSqlModel model;
    tvFileController->setTvGidSqlModel(&model);

    //When
    bool isInitOk = tvFileController->initTvFileController();



    //Expected
    QVERIFY2(isInitOk, "Failure init");
    if(!isInitOk){
        qDebug() << "select" << model.lastError().text();
    }
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

bool TVFileControllerTest::connectToSQL_DB()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(":memory:");
//    dbase.setDatabaseName("tvgid.sql");
    if (!dbase.open()) {
        qDebug() << "not connect";
        return false;
    }
    return true;
}


QTEST_APPLESS_MAIN(TVFileControllerTest)

#include "tst_tvfilecontrollertest.moc"
