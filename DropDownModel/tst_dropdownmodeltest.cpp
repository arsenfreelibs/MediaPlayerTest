#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Data/TVModels/TVCategoryModel.h"
#include "../../../MediaPlayer/src/Data/MoviesModels/MovieSortModels.h"
#include <QAbstractListModel>
class DropDownModelTest : public QObject
{
    Q_OBJECT
    
public:
    DropDownModelTest();
    
private Q_SLOTS:
    void testCreateInstance_TVCategoryModel();
    void testColumnCount_TVCategoryModel();
    void testRowCount_TVCategoryModel();
    void testRoleName_TVCategoryModel();
    void testRoleGenre_TVCategoryModel();
    void testRoleGenreId_TVCategoryModel();
    void testVolidName_TVCategoryModel();
    void testVolidGenre_TVCategoryModel();
    void testVolidGenreid_TVCategoryModel();
    void testLessIndex_TVCategoryModel();
    void testMoreIndex_TVCategoryModel();

    void testCreateInstance_MovieSortModels();
    void testColumnCount_MovieSortModels();
    void testRowCount_MovieSortModels();
    void testRoleName_MovieSortModels();
    void testRoleSortingField_MovieSortModels();
    void testVolidName_MovieSortModels();
    void testVolidVideoSortingField_MovieSortModels();
    void testLessIndex_MovieSortModels();
    void testMoreIndex_MovieSortModels();
};

DropDownModelTest::DropDownModelTest()
{
}

void DropDownModelTest::testCreateInstance_TVCategoryModel()
{
    TVCategoryModel tvCategoryModel;
    QVERIFY2(true, "Failure");
}
void DropDownModelTest::testColumnCount_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;

    //WHEN
    int column = tvCategoryModel.columnCount();

    //EXPECTED
    QCOMPARE(column, 1);
}
void DropDownModelTest::testRowCount_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;

    //WHEN
    int row = tvCategoryModel.rowCount();

    //EXPECTED
    QCOMPARE(row, 10);
}
void DropDownModelTest::testRoleName_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    QHash<int,QByteArray> roles;
    //WHEN
    roles = tvCategoryModel.roleNames();
    QByteArray name = roles.value(TVCategoryModel :: NameRole);
    //EXPECTED
    QCOMPARE(name, QByteArray("name"));
}
void DropDownModelTest::testRoleGenre_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    QHash<int,QByteArray> roles;
    //WHEN
    roles = tvCategoryModel.roleNames();
    QByteArray genre = roles.value(TVCategoryModel :: GenresRole);
    //EXPECTED
    QCOMPARE(genre, QByteArray("genre"));
}
void DropDownModelTest::testRoleGenreId_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    QHash<int,QByteArray> roles;
    //WHEN
    roles = tvCategoryModel.roleNames();
    QByteArray genreid = roles.value(TVCategoryModel :: IdRole);
    //EXPECTED
    QCOMPARE(genreid, QByteArray("genre_id"));
}
void DropDownModelTest::testVolidName_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    int countRow = tvCategoryModel.rowCount();
    QModelIndex indx = tvCategoryModel.index(0, 0, QModelIndex());
    bool flagEmptyData = false;
    //WHEN
    for (int i = 0; i < countRow; i++)
    {
        indx = tvCategoryModel.index(i, 0, QModelIndex());
        if ( tvCategoryModel.data(indx, TVCategoryModel :: NameRole).toString().isEmpty())
        {
             flagEmptyData = true;
        }
    }
    //EXPECTED
    QCOMPARE(flagEmptyData, false);
}
void DropDownModelTest::testVolidGenre_TVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    int countRow = tvCategoryModel.rowCount();
    QModelIndex indx = tvCategoryModel.index(0, 0, QModelIndex());
    bool flagEmptyData = false;
    //WHEN
    for (int i = 0; i < countRow; i++)
    {
        indx = tvCategoryModel.index(i, 0, QModelIndex());
        if ( tvCategoryModel.data(indx, TVCategoryModel ::GenresRole).toString().isEmpty())
        {
             flagEmptyData = true;
        }
    }
    //EXPECTED
    QCOMPARE(flagEmptyData, false);
}
void DropDownModelTest::testVolidGenreid_TVCategoryModel()
{
    //GIVEN
   QMap<int, int> mapRoleId;
   int roleId;
   TVCategoryModel tvCategoryModel;
   int countRow = tvCategoryModel.rowCount();
   QModelIndex indx = tvCategoryModel.index(0, 0, QModelIndex());
   //WHEN
   for (int i = 0; i < countRow; i++)
   {
       indx = tvCategoryModel.index(i, 0, QModelIndex());
       roleId = tvCategoryModel.data(indx, TVCategoryModel ::IdRole).toInt();
       mapRoleId.insert(roleId, roleId);
   }
   //EXPECTED
   QCOMPARE(countRow, mapRoleId.size());
}
void DropDownModelTest::testLessIndex_TVCategoryModel()
{
   //GIVEN
   QVariant dataModel;
   TVCategoryModel tvCategoryModel;
   //WHEN
   QModelIndex indx = tvCategoryModel.index(-1, 0, QModelIndex());
   dataModel = tvCategoryModel.data(indx, TVCategoryModel ::IdRole);
   //EXPECTED
   QCOMPARE(dataModel.canConvert(QVariant::Int), false);
}
void DropDownModelTest::testMoreIndex_TVCategoryModel()
{
   //GIVEN
   QVariant dataModel;
   TVCategoryModel tvCategoryModel;
   QString msg;
   int countRow = tvCategoryModel.rowCount();
   //WHEN
   QModelIndex indx = tvCategoryModel.index(countRow, 0, QModelIndex());
   dataModel = tvCategoryModel.data(indx, TVCategoryModel :: IdRole);
   //EXPECTED
   //msg = QString("countRow - %1, indx.row() - %2").arg(countRow).arg(indx.row());
   //QWARN (msg.toLocal8Bit().constData());
   QCOMPARE(dataModel.canConvert(QVariant::Int), false);
}
//************************************************************************
void DropDownModelTest::testCreateInstance_MovieSortModels()
{
    MovieSortModels movieSortModels;
    QVERIFY2(true, "Failure");
}
void DropDownModelTest::testColumnCount_MovieSortModels()
{
    //GIVEN
    MovieSortModels movieSortModels;

    //WHEN
    int column = movieSortModels.columnCount();

    //EXPECTED
    QCOMPARE(column, 1);
}
void DropDownModelTest::testRowCount_MovieSortModels()
{
    //GIVEN
    MovieSortModels movieSortModels;

    //WHEN
    int row = movieSortModels.rowCount();

    //EXPECTED
    QCOMPARE(row, 4);
}
void DropDownModelTest::testRoleName_MovieSortModels()
{
    //GIVEN
    MovieSortModels movieSortModels;
    QHash<int,QByteArray> roles;
    //WHEN
    roles = movieSortModels.roleNames();
    QByteArray name = roles.value(MovieSortModels :: NameRole);
    //EXPECTED
    QCOMPARE(name, QByteArray("name"));
}
void DropDownModelTest::testRoleSortingField_MovieSortModels()
{
    //GIVEN
    MovieSortModels movieSortModels;
    QHash<int,QByteArray> roles;
    //WHEN
    roles = movieSortModels.roleNames();
    QByteArray genre = roles.value(MovieSortModels ::SortingFieldRole);
    //EXPECTED
    QCOMPARE(genre, QByteArray("sortingField"));
}

void DropDownModelTest::testVolidName_MovieSortModels()
{
    //GIVEN
    MovieSortModels movieSortModels;
    int countRow = movieSortModels.rowCount();
    QModelIndex indx = movieSortModels.index(0, 0, QModelIndex());
    bool flagEmptyData = false;
    //WHEN
    for (int i = 0; i < countRow; i++)
    {
        indx = movieSortModels.index(i, 0, QModelIndex());
        if ( movieSortModels.data(indx, MovieSortModels :: NameRole).toString().isEmpty())
        {
             flagEmptyData = true;
        }
    }
    //EXPECTED
    QCOMPARE(flagEmptyData, false);
}
void DropDownModelTest::testVolidVideoSortingField_MovieSortModels()
{
    //GIVEN
   QMap<int, int> mapRoleId;
   int roleId;
   MovieSortModels movieSortModels;
   int countRow = movieSortModels.rowCount();
   QModelIndex indx = movieSortModels.index(0, 0, QModelIndex());
   //WHEN
   for (int i = 0; i < countRow; i++)
   {
       indx = movieSortModels.index(i, 0, QModelIndex());
       roleId = movieSortModels.data(indx, MovieSortModels :: SortingFieldRole).toInt();
       mapRoleId.insert(roleId, roleId);
   }
   //EXPECTED
   QCOMPARE(countRow, mapRoleId.size());
}
void DropDownModelTest::testLessIndex_MovieSortModels()
{
   //GIVEN
   QVariant dataModel;
   MovieSortModels movieSortModels;
   //WHEN
   QModelIndex indx = movieSortModels.index(-1, 0, QModelIndex());
   dataModel = movieSortModels.data(indx, MovieSortModels :: SortingFieldRole);
   //EXPECTED
   QCOMPARE(dataModel.canConvert(QVariant::Int), false);
}
void DropDownModelTest::testMoreIndex_MovieSortModels()
{
   //GIVEN
   QVariant dataModel;
   MovieSortModels movieSortModels;
   QString msg;
   int countRow = movieSortModels.rowCount();
   //WHEN
   QModelIndex indx = movieSortModels.index(countRow, 0, QModelIndex());
   dataModel = movieSortModels.data(indx, MovieSortModels :: SortingFieldRole);
   //EXPECTED
   //msg = QString("countRow - %1, indx.row() - %2").arg(countRow).arg(indx.row());
   //QWARN (msg.toLocal8Bit().constData());
   QCOMPARE(dataModel.canConvert(QVariant::Int), false);
}
QTEST_APPLESS_MAIN(DropDownModelTest)

#include "tst_dropdownmodeltest.moc"
