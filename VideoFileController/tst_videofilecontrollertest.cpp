#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Controllers/Files/AbstractVideoFileController.h>
#include <../../../MediaPlayer/src/Controllers/Files/VideoFileController.h>
#include <../../../MediaPlayer/src/Data/SqlModels/VideoSqlTableModel.h>

class VideoFileControllerTest : public QObject
{
    Q_OBJECT
    
public:
    VideoFileControllerTest();
    
private Q_SLOTS:
    void testCreateAbstractVideoFileController();
    void testCreateVideoFileController();

    void test_SaveDownloadedVideoData_VideoFileController();

    void test_create_VideoSqlTableModel();
    void test_getDataWithoutConnectionToDB_VideoSqlTableModel();
    void getCountWithoutConnectionToDBTest_VideoSqlTableModel();
    void initializeModelTest();
    void getCountWhenConnectionToDBTest();
    void roleConstantTest();

private:
    bool connectToSQL_DB();
    bool createSQLTable();
    bool fillSQLTable(QString table);
    void initializeModel(QSqlTableModel *model);

};

VideoFileControllerTest::VideoFileControllerTest()
{
}

void VideoFileControllerTest::testCreateAbstractVideoFileController()
{
    //given

    //when
    AbstractVideoFileController abstractVideoFileController;

    //expexted
    QVERIFY2(true, "");
}

void VideoFileControllerTest::testCreateVideoFileController()
{
    //given

    //when
    VideoFileController abstractVideoFileController;

    //expexted
    QVERIFY2(true, "");
}

void VideoFileControllerTest::test_SaveDownloadedVideoData_VideoFileController()
{
    //given
    VideoFileController videoFileController;
    MovieItemDataAccess item;

    //when
    bool result = videoFileController.SaveDownloadedVideoData(item, "");


    //expexted
    QVERIFY2(result, "Fail saving video data");
}

void VideoFileControllerTest::test_create_VideoSqlTableModel()
{
    //given

    //when
    VideoSqlTableModel model;

    //expected
    QVERIFY2(true, "");

}

void VideoFileControllerTest::test_getDataWithoutConnectionToDB_VideoSqlTableModel()
{
    //Given
    QSqlTableModel *model = new VideoSqlTableModel();
    QModelIndex index;

    //When
    QVariant value = model->data(index);


    //Expected
    if (value.isValid()){
        QVERIFY2(false, "Failure connect to DB without connection");
    }else{
        QVERIFY2(true, "");
    }
}


void VideoFileControllerTest::getCountWithoutConnectionToDBTest_VideoSqlTableModel()
{
    //Given
    QSqlTableModel *model = new VideoSqlTableModel();

    //When
    int count = model->rowCount();

    //Expected
    QVERIFY2(count == 0, "Failure, count not 0 without connection");
}

void VideoFileControllerTest::initializeModelTest()
{
    //Given
    connectToSQL_DB();
    VideoSqlTableModel *model = new VideoSqlTableModel();

    //When
    bool isInit = model->initializeModel();

    //Expected
    QVERIFY2(isInit,"fail init model");
}

void VideoFileControllerTest::getCountWhenConnectionToDBTest()
{
    //Given
    connectToSQL_DB();
    VideoSqlTableModel *model = new VideoSqlTableModel();
    model->initializeModel();
    fillSQLTable(VIDEO_MODEL_SQL_TABLE);
    model->select();

    //When
    int count = model->rowCount();

    //Expected
    QVERIFY2(count==2,"fail,has no elements");
}

void VideoFileControllerTest::roleConstantTest()
{
    //Expected
//    QCOMPARE(Qt::UserRole + 1, VideoSqlTableModel::ProgramNameRole);
//    QCOMPARE(Qt::UserRole + 2, VideoSqlTableModel::LogoImgLinkRole);
//    QCOMPARE(Qt::UserRole + 3, VideoSqlTableModel::ChanalNameRole);
//    QCOMPARE(Qt::UserRole + 4, VideoSqlTableModel::DurationRole);
//    QCOMPARE(Qt::UserRole + 5, VideoSqlTableModel::DateRole);
//    QCOMPARE(Qt::UserRole + 6, VideoSqlTableModel::SizeRole);

    QVERIFY2(false, "need to write this test");

}

bool VideoFileControllerTest::connectToSQL_DB()
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

bool VideoFileControllerTest::createSQLTable()
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

bool VideoFileControllerTest::fillSQLTable(QString table)
{
    QSqlQuery a_query;

    QString str_insert = "INSERT INTO "+table+"(id, program_name, logo_img_link, chanal_name, duration, date, size) "
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

void VideoFileControllerTest::initializeModel(QSqlTableModel *model)
{
    model->setTable("my_table");
    model->select();
}


QTEST_APPLESS_MAIN
(VideoFileControllerTest)

#include "tst_videofilecontrollertest.moc"
