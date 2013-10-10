#include <QString>
#include <QtTest>
#include <QSqlQueryModel>
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

QTEST_APPLESS_MAIN(TVGidSqlModelTest)

#include "tst_tvgidsqlmodeltest.moc"
