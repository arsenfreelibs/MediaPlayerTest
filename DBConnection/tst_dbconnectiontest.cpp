#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/DB/AbstractDBConnector.h>
#include <../../../MediaPlayer/src/DB/DBConnector.h>

class DBConnectionTest : public QObject
{
    Q_OBJECT
    
public:
    DBConnectionTest();
    
private Q_SLOTS:
    void createDBConnector();
    void setDbNameTest();
    void connectToSQLTableTest();
};

DBConnectionTest::DBConnectionTest()
{
}

void DBConnectionTest::createDBConnector()
{
    //Given

    //When
    AbstractDBConnector *dbConnector = new DBConnector();

    //Expected
    QVERIFY2(dbConnector!=NULL, "Failure cannot create obj");
}

void DBConnectionTest::setDbNameTest()
{
    //Given
    DBConnector *dbConnector = new DBConnector();

    //When
    dbConnector->setDbName(":memory:");

    //Expected
    QVERIFY2(dbConnector->dbName() == ":memory:", "Failure setDbName error");
}

void DBConnectionTest::connectToSQLTableTest()
{
    //Given
    DBConnector dbConnector;
    dbConnector.setDbName(":memory:");

    AbstractDBConnector *abstrDbConnector = &dbConnector;


    //When
    bool isConnest = abstrDbConnector->connectToSqlDB();


    //Expected
     QVERIFY2(isConnest, "Failure scan not connect to DB");

}

QTEST_APPLESS_MAIN(DBConnectionTest)

#include "tst_dbconnectiontest.moc"
