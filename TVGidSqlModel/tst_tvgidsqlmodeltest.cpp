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
    void roleConstantTest();
    void getProgramNameTest();

private:
    bool connectToSQLTable();
    bool createSQLTable();
    bool fillSQLTable();
    bool dropSQLTable();
    void initializeModel(QSqlQueryModel *model);

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
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    //When
    int count = model->rowCount();

    //Expected
    QVERIFY2(count==2,"fail,has no elements");
}

void TVGidSqlModelTest::roleConstantTest()
{
    //Expected
    QCOMPARE(Qt::UserRole + 1, TVGidSqlModel::PROGRAM_NAME);
    QCOMPARE(Qt::UserRole + 2, TVGidSqlModel::LOGO_IMG_LINK);
    QCOMPARE(Qt::UserRole + 3, TVGidSqlModel::CHANAL_NAME);
    QCOMPARE(Qt::UserRole + 4, TVGidSqlModel::DURATION);
    QCOMPARE(Qt::UserRole + 5, TVGidSqlModel::DATE);
    QCOMPARE(Qt::UserRole + 6, TVGidSqlModel::SIZE);


}

void TVGidSqlModelTest::getProgramNameTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(0,0);
    int role = TVGidSqlModel::PROGRAM_NAME;


    //When
    QVariant value = model->data(index,role);

    //Expected
    if (value.isValid()){
        if(value.toString().length()>0){
            if(value.toString() == "prg1"){
                QVERIFY2(true, "");
            }else{
                QVERIFY2(false, "strcompare error");
            }
        }else{
            QVERIFY2(false, "strlen==0");
        }
    }else{
        QVERIFY2(false, "value not valid");
    }

}

bool TVGidSqlModelTest::connectToSQLTable()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(":memory:");
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
            "id integer PRIMARY KEY NOT NULL, "
            "program_name VARCHAR(100), "
            "logo_img_link VARCHAR(100), "
            "chanal_name VARCHAR(100), "
            "duration integer, "
            "date VARCHAR(100), "
            "size integer"
            ");";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "cannot cleate table";
    }

}

bool TVGidSqlModelTest::fillSQLTable()
{
    QSqlQuery a_query;

    QString str_insert = "INSERT INTO my_table(id, program_name, logo_img_link, chanal_name, duration, date, size) "
            "VALUES (%1, '%2', '%3', '%4', %5, '%6', %7);";
    QString str = str_insert.arg("1")
            .arg("prg1")
            .arg("link1")
            .arg("chnl1")
            .arg("10")
            .arg("10.10.2013")
            .arg("100");

    bool b = a_query.exec(str);

    str = str_insert.arg("2")
            .arg("prg2")
            .arg("link2")
            .arg("chnl2")
            .arg("20")
            .arg("12.10.2013")
            .arg("200");

    b &= a_query.exec(str);


    if (!b) {
        qDebug() << "error when insert data";
    }
}

bool TVGidSqlModelTest::dropSQLTable()
{
}

void TVGidSqlModelTest::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from my_table");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("number"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("address"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
}

QTEST_APPLESS_MAIN(TVGidSqlModelTest)

#include "tst_tvgidsqlmodeltest.moc"
