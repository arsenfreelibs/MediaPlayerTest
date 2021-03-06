#include <QString>
#include <QtTest>
#include "../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp"
#include "../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.cpp"
#include "../../../MediaPlayer/src/Controllers/TV/PreSettingVisitorPreviewPlaylistControllerImpl.h"
#include "PlaylistModelFake.h"
#include "PreviewPlaylistControllerSettableFake.h"

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

    void test_sdFilter();
    void test_hdFilter();

    void test_Visitor_setSettingVisitor();
    void test_Visitor_loadSettings_noObjectForVisit();
    void test_Visitor_loadSettings_noSetting();
    void test_Visitor_loadSettings();
    void test_Visitor_saveSettings();

    void test_setSettingVisitorIntoController();
    void test_saveIndexToSettingWhenTvCategoryModelIntexChange();
    void test_saveFiltersToSettingWhenHdSdFiltersChanged();

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

void PreviewPlaylistControllerTest::test_sdFilter()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);

    //WHEN
    previewPlaylistController.setSD_Filter(false);
    bool sdFilter1 = previewPlaylistController.sdFilter();
    previewPlaylistController.setSD_Filter(true);
    bool sdFilter2 = previewPlaylistController.sdFilter();


    //EXPECTED
    QVERIFY2(sdFilter1 == false, "Failure");
    QVERIFY2(sdFilter2, "Failure");
}

void PreviewPlaylistControllerTest::test_hdFilter()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);

    //WHEN
    previewPlaylistController.setHD_Filter(false);
    bool hdFilter1 = previewPlaylistController.hdFilter();
    previewPlaylistController.setHD_Filter(true);
    bool hdFilter2 = previewPlaylistController.hdFilter();


    //EXPECTED
    QVERIFY2(hdFilter1 == false, "Failure");
    QVERIFY2(hdFilter2, "Failure");}

void PreviewPlaylistControllerTest::test_Visitor_setSettingVisitor()
{
    //GIVEN

    PreviewPlaylistControllerSettableFake controllerSettable;
    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&controllerSettable);


    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    //when
    preSettingVisitor->setSettings(settings);

    //expected
    QCOMPARE(settings,visitor.settings());
}

void PreviewPlaylistControllerTest::test_Visitor_loadSettings_noObjectForVisit()
{

    //GIVEN

    PreSettingVisitorPreviewPlaylistControllerImpl visitor(NULL);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);


    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected
    QCOMPARE(status, PreSettingVisitor::IllgalArgument);
}

void PreviewPlaylistControllerTest::test_Visitor_loadSettings_noSetting()
{

    //GIVEN

    PreviewPlaylistControllerSettableFake controllerSettable;
    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&controllerSettable);

    PreSettingVisitor *preSettingVisitor = &visitor;

    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected
    QCOMPARE(status, PreSettingVisitor::IllgalArgument);
}

void PreviewPlaylistControllerTest::test_Visitor_loadSettings()
{
    //GIVEN

    PreviewPlaylistControllerSettableFake controllerSettable;
    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&controllerSettable);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);
    settings->setTvCategoryModelIntex(5);

    //when
    preSettingVisitor->loadSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected

    QCOMPARE(controllerSettable.getTvCategoryModelIntex(), 5);
    QCOMPARE(status, PreSettingVisitor::Success);
}

void PreviewPlaylistControllerTest::test_Visitor_saveSettings()
{
    //GIVEN

    PreviewPlaylistControllerSettableFake controllerSettable;
    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&controllerSettable);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);
    settings->setTvCategoryModelIntex(5);

    controllerSettable.setFiltersByTvCategoryModelIntex(4);
    //when
    preSettingVisitor->saveSettings();
    PreSettingVisitor::Statuses status = preSettingVisitor->getStatus();


    //expected

    QCOMPARE(settings->tvCategoryModelIntex(), 4);
    QCOMPARE(status, PreSettingVisitor::Success);
}

void PreviewPlaylistControllerTest::test_setSettingVisitorIntoController()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);


    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&previewPlaylistController);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);
    settings->setTvCategoryModelIntex(3);

    bool sdFilter = previewPlaylistController.sdFilter();
    settings->setSdFilter(!sdFilter);

    bool hdFilter = previewPlaylistController.hdFilter();
    settings->setHdFilter(!hdFilter);


    //WHEN
    previewPlaylistController.setSettingVisitor(preSettingVisitor);


    //EXPECTED
    QCOMPARE(previewPlaylistController.getTvCategoryModelIntex(), 3);
    QCOMPARE(previewPlaylistController.sdFilter(), !sdFilter);
    QCOMPARE(previewPlaylistController.hdFilter(), !hdFilter);
}

void PreviewPlaylistControllerTest::test_saveIndexToSettingWhenTvCategoryModelIntexChange()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);


    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&previewPlaylistController);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);
    settings->setTvCategoryModelIntex(3);

    previewPlaylistController.setSettingVisitor(preSettingVisitor);

    //WHEN
    previewPlaylistController.setFiltersByTvCategoryModelIntex(2);

    //EXPECTED
    QCOMPARE(settings->tvCategoryModelIntex(), 2);
}

void PreviewPlaylistControllerTest::test_saveFiltersToSettingWhenHdSdFiltersChanged()
{
    //GIVEN
    PreviewPlaylistController previewPlaylistController;

    TVCategoryModel tvCategoryModel;
    previewPlaylistController.setTVCategoryModel(&tvCategoryModel);

    PlaylistModelFake model;
    previewPlaylistController.setPlaylistModel(&model);


    PreSettingVisitorPreviewPlaylistControllerImpl visitor(&previewPlaylistController);

    Settings *settings = Settings::sharedInstance();
    PreSettingVisitor *preSettingVisitor = &visitor;

    preSettingVisitor->setSettings(settings);

    bool sdFilter = previewPlaylistController.sdFilter();
    settings->setSdFilter(!sdFilter);

    bool hdFilter = previewPlaylistController.hdFilter();
    settings->setHdFilter(!hdFilter);

    previewPlaylistController.setSettingVisitor(preSettingVisitor);

    //WHEN
    previewPlaylistController.setSD_Filter(sdFilter);
    previewPlaylistController.setHD_Filter(hdFilter);

    //EXPECTED
    QCOMPARE(settings->sdFilter(), sdFilter);
    QCOMPARE(settings->hdFilter(), hdFilter);
}

QTEST_APPLESS_MAIN(PreviewPlaylistControllerTest)

#include "tst_previewplaylistcontrollertest.moc"
