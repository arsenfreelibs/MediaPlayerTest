#include <QString>
#include <QtTest>
#include <QSqlQueryModel>
#include <QtSql>
#include <../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.h>


class TVGidSqlModelTest : public QObject
{
    Q_OBJECT
    
public:
    TVGidSqlModelTest();
    
private Q_SLOTS:
    void createTest();
    void getDataWithoutConnectionToDBTest();
    void getCountWithoutConnectionToDBTest();
    void getCountWhenConnectionToDBTest();

private:
    bool connectToSQLTable();
    bool createSQLTable();
    bool fillSQLTable();
    bool dropSQLTable();

};

TVGidSqlModelTest::TVGidSqlModelTest()
{
}

void TVGidSqlModelTest::createTest()
{
    //Given
    QSqlQueryModel *model = new TVGidSqlModel();

    //Expected
    QVERIFY2(true, "Failure");
}

void TVGidSqlModelTest::getDataWithoutConnectionToDBTest()
{
    //Given
    QSqlQueryModel *model = new TVGidSqlModel();
    QModelIndex index;

    //When
    QVariant value = model->data(index);


    //Expected
    if (value.isValid()){
        QVERIFY2(false, "Failure connect to DB without connection");
    }else{
        QVERIFY2(true, "Failure");
    }


}

void TVGidSqlModelTest::getCountWithoutConnectionToDBTest()
{
    //Given
    QSqlQueryModel *model = new TVGidSqlModel();

    //When
    int count = model->rowCount();

    //Expected
    if (count==0){
        QVERIFY2(true, "Failure connect to DB without connection");
    }else{
        QVERIFY2(false, "Failure");
    }

}

void TVGidSqlModelTest::getCountWhenConnectionToDBTest()
{
    //Given
    connectToSQLTable();
//    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    qDebug() << "1";
//    model->setQuery("SELECT * FROM my_table'");

    //When
    int count = model->rowCount();

    //Expected
    if (count==0){
        QVERIFY2(false,"fail,has no elements");
    }else{
        QVERIFY2(true,"ok");
    }
}

bool TVGidSqlModelTest::connectToSQLTable()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "not connect";
        return false;
    }
}

bool TVGidSqlModelTest::createSQLTable()
{
    QSqlQuery a_query;
    // DDL query
    QString str = "CREATE TABLE my_table ("
            "number integer PRIMARY KEY NOT NULL, "
            "address VARCHAR(255), "
            "age integer"
            ");";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Вроде не удается создать таблицу, провертье карманы!";
    }

}

bool TVGidSqlModelTest::fillSQLTable()
{
    QString str_insert = "INSERT INTO my_table(number, address, age) "
            "VALUES (%1, '%2', %3);";
    QString str = str_insert.arg("14")
            .arg("hello world str.")
            .arg("37");
    QSqlQuery a_query;
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }
}

bool TVGidSqlModelTest::dropSQLTable()
{
}

QTEST_APPLESS_MAIN(TVGidSqlModelTest)

#include "tst_tvgidsqlmodeltest.moc"
