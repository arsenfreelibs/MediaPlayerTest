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
    void roleNamesTest();
    void getProgramNameTest();
    void getLogoImgLinkTest();
    void getWrongIndexLogoImgLinkTest();
    void getChanalNameTest();
    void getDurationRoleTest();
    void getDateRoleTest();
    void getSizeRoleTest();



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
    QCOMPARE(Qt::UserRole + 1, TVGidSqlModel::ProgramNameRole);
    QCOMPARE(Qt::UserRole + 2, TVGidSqlModel::LogoImgLinkRole);
    QCOMPARE(Qt::UserRole + 3, TVGidSqlModel::ChanalNameRole);
    QCOMPARE(Qt::UserRole + 4, TVGidSqlModel::DurationRole);
    QCOMPARE(Qt::UserRole + 5, TVGidSqlModel::DateRole);
    QCOMPARE(Qt::UserRole + 6, TVGidSqlModel::SizeRole);


}

void TVGidSqlModelTest::roleNamesTest()
{
    //Given
    QSqlQueryModel *model = new TVGidSqlModel();
    QHash<int,QByteArray> roles;

    //When
    roles = model->roleNames();

    //Expected
    if(roles[TVGidSqlModel::ProgramNameRole] != "programName"){
        QVERIFY2(false, "incorrect programName role");
    }
    if(roles[TVGidSqlModel::LogoImgLinkRole] != "logoImgLink"){
        QVERIFY2(false, "incorrect programName role");
    }
    if(roles[TVGidSqlModel::ChanalNameRole] != "chanalName"){
        QVERIFY2(false, "incorrect programName role");
    }
    if(roles[TVGidSqlModel::DurationRole] != "duration"){
        QVERIFY2(false, "incorrect programName role");
    }
    if(roles[TVGidSqlModel::DateRole] != "date"){
        QVERIFY2(false, "incorrect programName role");
    }
    if(roles[TVGidSqlModel::SizeRole] != "size"){
        QVERIFY2(false, "incorrect programName role");
    }
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
    int role = TVGidSqlModel::ProgramNameRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toString() == "prg1", "strcompare error");
}

void TVGidSqlModelTest::getLogoImgLinkTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(1,0);
    int role = TVGidSqlModel::LogoImgLinkRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toString() == "link2", "strcompare error");
}

void TVGidSqlModelTest::getWrongIndexLogoImgLinkTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    int count = model->rowCount();
    QModelIndex index = model->index(count+1,0);
    int role = TVGidSqlModel::LogoImgLinkRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toString() == "", "strcompare error");
}

void TVGidSqlModelTest::getChanalNameTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(1,0);
    int role = TVGidSqlModel::ChanalNameRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toString() == "chnl2", "compare error");
}

void TVGidSqlModelTest::getDurationRoleTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(1,0);
    int role = TVGidSqlModel::DurationRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toInt() == 20, "compare error");
}

void TVGidSqlModelTest::getDateRoleTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(0,0);
    int role = TVGidSqlModel::DateRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toString() == "10.10.2013", "compare error");
}

void TVGidSqlModelTest::getSizeRoleTest()
{
    //Given
    connectToSQLTable();
    createSQLTable();
    fillSQLTable();
    QSqlQueryModel *model = new TVGidSqlModel();
    initializeModel(model);

    QModelIndex index = model->index(1,0);
    int role = TVGidSqlModel::SizeRole;


    //When
    QVariant value = model->data(index,role);

    //Expected
    QVERIFY2(value.toInt() == 200, "compare error");
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
//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("number"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("address"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
}

QTEST_APPLESS_MAIN(TVGidSqlModelTest)

#include "tst_tvgidsqlmodeltest.moc"
