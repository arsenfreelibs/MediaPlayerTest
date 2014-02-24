#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp"
#include "../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.cpp"
#include "PlaylistModelFake.h"

class PreviewPlaylistControllerTest : public QObject
{
    Q_OBJECT
    
public:
    PreviewPlaylistControllerTest();
    
private Q_SLOTS:
    void test_createPreviewPlaylistController();
    void test_setGetTVCategoryModel();
    void test_setFiltersByTvCategoryModelIntex_all();
    void test_setFiltersByTvCategoryModelIntex_notSetTvCategoryModel();
    void test_setFiltersByTvCategoryModelIntex_favorite();
    void test_setFiltersByTvCategoryModelIntex_anyCategory();
    void test_getTvCategoryModelIntex();
};

PreviewPlaylistControllerTest::PreviewPlaylistControllerTest()
{
}

void PreviewPlaylistControllerTest::test_createPreviewPlaylistController()
{
    PreviewPlaylistController *previewPlaylistController = new PreviewPlaylistController();
    QVERIFY2(previewPlaylistController != NULL, "Failure");
}

void PreviewPlaylistControllerTest::test_setGetTVCategoryModel()
{
    //GIVEN
    TVCategoryModel tvCategoryModel;
    PreviewPlaylistController previewPlaylistController;


    //WHEN
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);
    QAbstractListModel *listModel = previewPlaylistController.getTVCategoryModel();

    //EXPECTED
    QVERIFY2(listModel == &tvCategoryModel, "Failure");
}

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex_all()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);
    model.setActiveGenreFilter(true);
    model.setActiveFavoriteFilter(true);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(0);

    //EXPECTED
    QVERIFY2(model.getActiveGenreFilter() == false, "Failure");
    QVERIFY2(model.getActiveFavoriteFilter() == false, "Failure");
}

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex_notSetTvCategoryModel()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);
    model.setActiveGenreFilter(true);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(0);

    //EXPECTED
    QVERIFY2(model.getActiveGenreFilter() == false, "Failure");
    QVERIFY2(model.getActiveFavoriteFilter() == false, "Failure");
}

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex_favorite()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);
    model.setActiveGenreFilter(true);
    model.setActiveFavoriteFilter(false);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(1);

    //EXPECTED
    QVERIFY2(model.getActiveGenreFilter() == false, "Failure");
    QVERIFY2(model.getActiveFavoriteFilter() == true, "Failure");
}

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex_anyCategory()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);
    model.setActiveGenreFilter(true);
    model.setActiveFavoriteFilter(false);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(3);

    //EXPECTED
    QVERIFY2(model.getActiveGenreFilter() == true, "Failure");
    QVERIFY2(model.getActiveFavoriteFilter() == false, "Failure");
    QCOMPARE(model.getGenreID(),(int)TVCategoryModel::MUSIC);
}

void PreviewPlaylistControllerTest::test_getTvCategoryModelIntex()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);

    previewPlaylistController.setFiltersByTvCategoryModelIntex(3);

    //WHEN
    int index = previewPlaylistController.getTvCategoryModelIntex();

    //EXPECTED
    QCOMPARE(index,3);
}

QTEST_APPLESS_MAIN(PreviewPlaylistControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
