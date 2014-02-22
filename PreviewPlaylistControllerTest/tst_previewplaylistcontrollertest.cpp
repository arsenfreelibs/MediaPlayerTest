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
    void test_setFiltersByTvCategoryModelIntex();
    void test_setFiltersByTvCategoryModelIntex_notSetTvCategoryModel();
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

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);
    model.setActiveGenreFilter(true);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(0);

    //EXPECTED
    QVERIFY2(model.getActiveGenreFilter() == false, "Failure");
}

void PreviewPlaylistControllerTest::test_setFiltersByTvCategoryModelIntex_notSetTvCategoryModel()
{
    QVERIFY2(false, "Failure");
}


QTEST_APPLESS_MAIN(PreviewPlaylistControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
