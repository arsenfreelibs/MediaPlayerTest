#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Data/PlaylistModel.h>
#include <../../../MediaPlayer/src/qt-json/json.h>
#include <QList>
#include <../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntry.h>
#include <../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntryDecorator.h>
#include <../../../MediaPlayer/src/Data/TvModelCollections/ListFilterProcessor.h>
#include <../../../MediaPlayer/src/Data/TvModelCollections/QualityListFilterProcessor.h>


class PlaylistModelTest : public QObject
{
    Q_OBJECT
    
private:
    PlaylistModel playlistModel_;

    const int ELEMENT_COUNT_HD;
    const int ELEMENT_COUNT_SD;


public:
    PlaylistModelTest();
    
private Q_SLOTS:
    void test_columnCount();
    void test_rowCount_afterCreate();
    void test_rowCount_noElements();
    void test_rowCount_noHD_noSD();
    void test_rowCount_HD_noSD();
    void test_rowCount_noHD_SD();
    void test_rowCount_HD_SD();
    void test_populate();
    void test_removeAllEntries();
    void test_rowCount_after_removeAllEntries();
    void test_loadProgramInfoFromMap();
    void test_loadProgramInfoFromMap_with_sameStartTime();
    void test_createListPlaylistModelEntry();
    void test_addToListPlaylistModelEntry();
    void test_atFromoListPlaylistModelEntry();
    void test_createListModelEntryDecorator();
    void test_decorateEmptyListModelEntryDecorator();
    void test_decorateListModelEntryDecorator();
    void test_createListFilterProcessor();
    void test_baseIsVisibleElementListFilterProcessor();
    void test_decorateWithBaseFilterListModelEntryDecorator();
    void test_baseSetFiltenActiveListFilterProcessor();
    void test_notActiveDecorateWithBaseFilterListModelEntryDecorator();
    void test_atNotActiveDecorateWithBaseFilterListModelEntryDecorator();
    void test_appendNotActiveDecorateWithBaseFilterListModelEntryDecorator();
    void test_appendDecorateWithBaseFilterListModelEntryDecorator();
    void test_decorateWithSDFilterListModelEntryDecorator();
    void test_decorateWithHDFilterListModelEntryDecorator();
    void test_decorateWithSDHDFilterListModelEntryDecorator();
    void test_onOffDecorateWithSDFilterListModelEntryDecorator();
    void test_onOffDecorateWithSDHDFilterListModelEntryDecorator();


private:
    void addHDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countHD);
    void addHDElementToListOfEntries(ListModelEntry &listEntries, int countHD);

    void addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD);
    void addSDElementToListOfEntries(ListModelEntry &listEntries, int countSD);

    const QVariantMap createEPG(const QString &jsonStr);

};

PlaylistModelTest::PlaylistModelTest():
ELEMENT_COUNT_HD(4),ELEMENT_COUNT_SD(3)
{
}

void PlaylistModelTest::test_columnCount()
{

    //GIVEN


    //WHEN
    int column = playlistModel_.columnCount();

    //EXPECTED
    QCOMPARE(column, 1);
}

void PlaylistModelTest::test_rowCount_afterCreate()
{
    //GIVEN
    PlaylistModel playlistModel;

    //WHEN
    int row = playlistModel.rowCount();

    //EXPECTED
    QCOMPARE(row, 0);
}

void PlaylistModelTest::test_rowCount_noElements()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    playlistModel_.populate(entries);

    //WHEN
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, 0);
}
void PlaylistModelTest::test_rowCount_noHD_noSD()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.setHdFilter(false);
    playlistModel_.setSdFilter(false);
    playlistModel_.populate(entries);

    //WHEN
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, 0);
}

void PlaylistModelTest::test_rowCount_HD_noSD()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.setHdFilter(true);
    playlistModel_.setSdFilter(false);
    playlistModel_.populate(entries);

    //WHEN
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, ELEMENT_COUNT_HD);
}

void PlaylistModelTest::test_rowCount_noHD_SD()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.setHdFilter(false);
    playlistModel_.setSdFilter(true);
    playlistModel_.populate(entries);

    //WHEN
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, ELEMENT_COUNT_SD);
}

void PlaylistModelTest::test_rowCount_HD_SD()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.setHdFilter(true);
    playlistModel_.setSdFilter(true);
    playlistModel_.populate(entries);

    //WHEN
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);
}

void PlaylistModelTest::test_populate()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);

    //WHEN
    playlistModel_.populate(entries);
    int count = playlistModel_.entries().size();

    //EXPECTED
    QCOMPARE(count, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);
}

void PlaylistModelTest::test_removeAllEntries()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.populate(entries);
    int count = playlistModel_.entries().size();
    QCOMPARE(count, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);


    //WHEN
    playlistModel_.removeAllEntries();
    count = playlistModel_.entries().size();

    //EXPECTED
    QCOMPARE(count, 0);

}

void PlaylistModelTest::test_rowCount_after_removeAllEntries()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.populate(entries);
    int count = playlistModel_.entries().size();
    QCOMPARE(count, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);


    //WHEN
    playlistModel_.removeAllEntries();
    int row = playlistModel_.rowCount();

    //EXPECTED
    QCOMPARE(row, 0);
}

void PlaylistModelTest::test_loadProgramInfoFromMap()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.populate(entries);
    int count = playlistModel_.entries().size();
    QCOMPARE(count, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);
    const QVariantMap &epg = createEPG("{\"error\":0,\"epg\":{\"244\":[{\"name\":\"qwerty\",\"from\":1377428400,\"to\":1377446400},{\"name\":\"yyy\",\"from\":1377446400,\"to\":1377450000}],\"144\":[{\"name\":\"aaa\",\"from\":1377428400,\"to\":1377446400},{\"name\":\"bbb\",\"from\":1377446400,\"to\":1377450000},{\"name\":\"ccc\",\"from\":1377446420,\"to\":1377450020}]}}");


    //WHEN
    playlistModel_.loadProgramInfoFromMap(epg);

    //EXPECTED
    for(int i=0;i<playlistModel_.entries().size();i++)
    {
        PlaylistModelEntry &entry = playlistModel_.entries().at(i);
        if(entry.xmltvid()=="244"){
            QCOMPARE((int)entry.programs().size(), 2);
        }
        if(entry.xmltvid()=="144"){
            QCOMPARE((int)entry.programs().size(), 3);
        }
    }

}

void PlaylistModelTest::test_loadProgramInfoFromMap_with_sameStartTime()
{
    //GIVEN
    std::vector<PlaylistModelEntry> entries;
    addHDElementToEntries(entries,ELEMENT_COUNT_HD);
    addSDElementToEntries(entries,ELEMENT_COUNT_SD);
    playlistModel_.populate(entries);
    int count = playlistModel_.entries().size();
    QCOMPARE(count, ELEMENT_COUNT_SD+ELEMENT_COUNT_HD);
    const QVariantMap &epg = createEPG("{\"error\":0,\"epg\":{\"244\":[{\"name\":\"1\",\"from\":1377428400,\"to\":1377446400},{\"name\":\"2\",\"from\":1377428400,\"to\":1377446400},{\"name\":\"3\",\"from\":1377428400,\"to\":1377446400}]}}");


    //WHEN
    playlistModel_.loadProgramInfoFromMap(epg);

    //EXPECTED
    for(int i=0;i<playlistModel_.entries().size();i++)
    {
        PlaylistModelEntry &entry = playlistModel_.entries().at(i);
        if(entry.xmltvid()=="244"){
            QCOMPARE((int)entry.programs().size(), 1);
            const QDateTime startTimeUTC(QDateTime::fromTime_t(1377428400));
            QCOMPARE(entry.program(startTimeUTC)->title_,(QString)"3");
        }
    }
}

void PlaylistModelTest::test_createListPlaylistModelEntry()
{
    //given

    //when
    ListModelEntry listModelEntry;

    //Expected
    QVERIFY2(true, "");
}

void PlaylistModelTest::test_addToListPlaylistModelEntry()
{
    //given
    ListModelEntry listModelEntry;

    //when
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    //Expected
    QVERIFY2(listModelEntry.size()==ELEMENT_COUNT_HD+ELEMENT_COUNT_SD, "wrong append");
}

void PlaylistModelTest::test_atFromoListPlaylistModelEntry()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    //when
    PlaylistModelEntry entry = listModelEntry.at(0);

    //Expected
   QCOMPARE(entry.title(), QString("chanal HD"));
}

void PlaylistModelTest::test_createListModelEntryDecorator()
{
    //given

    //when
    ListModelEntryDecorator decorator;

    //expected
    QVERIFY2(true, "");
}

void PlaylistModelTest::test_decorateEmptyListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;

    //when
    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    //expected
    QVERIFY2(decorator.size()==0, "");
}

void PlaylistModelTest::test_decorateListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    //when
    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    //expected
    QCOMPARE(decorator.size(),0); // because if not set FilterProcessor, will be FilterProcessor=null and not work filtration
}

void PlaylistModelTest::test_createListFilterProcessor()
{
    //given

    //when
    ListFilterProcessor proc;

    //expected
    QVERIFY2(true, "");
}

void PlaylistModelTest::test_baseIsVisibleElementListFilterProcessor()
{
    //given
    ListFilterProcessor proc;
    PlaylistModelEntry entry;

    //when
    bool res = proc.isVisibleElement(entry);

    //expected
    QVERIFY2(!res, "");
}

void PlaylistModelTest::test_baseSetFiltenActiveListFilterProcessor()
{
    //given
    ListFilterProcessor proc;
    PlaylistModelEntry entry;

    //when
    proc.setFilterActive(false);
    bool res = proc.isVisibleElement(entry);

    //expected
    QVERIFY2(res, "");
}

void PlaylistModelTest::test_decorateWithBaseFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    ListFilterProcessor proc;
    decorator.setListFilserProcessor(&proc);

    //when
    int size = decorator.size();

    //expected
    QCOMPARE(size,0);
}

void PlaylistModelTest::test_notActiveDecorateWithBaseFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    ListFilterProcessor proc;
    proc.setFilterActive(false);
    decorator.setListFilserProcessor(&proc);

    //when
    int size = decorator.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_HD+ELEMENT_COUNT_SD);
}

void PlaylistModelTest::test_atNotActiveDecorateWithBaseFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    ListFilterProcessor proc;
    proc.setFilterActive(false);
    decorator.setListFilserProcessor(&proc);

    //when
    PlaylistModelEntry entry = decorator.at(0);

    //Expected
    QCOMPARE(entry.title(), QString("chanal HD"));
}

void PlaylistModelTest::test_appendNotActiveDecorateWithBaseFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    ListFilterProcessor proc;
    proc.setFilterActive(false);
    decorator.setListFilserProcessor(&proc);

    PlaylistModelEntry entry;
    entry.setTitle("chanal2 HD");
    entry.setQuality("HD");
    entry.setXmltvid("245");

    //when
    decorator.append(entry);
    int size = decorator.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_HD+ELEMENT_COUNT_SD+1);
}

void PlaylistModelTest::test_appendDecorateWithBaseFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    ListFilterProcessor proc;
    decorator.setListFilserProcessor(&proc);

    PlaylistModelEntry entry;
    entry.setTitle("chanal2 HD");
    entry.setQuality("HD");
    entry.setXmltvid("245");

    //when
    decorator.append(entry);
    int size = decorator.size();

    //expected
    QCOMPARE(size,0);
}

void PlaylistModelTest::test_decorateWithSDFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    QualityListFilterProcessor proc;
    proc.setFilterString(PlaylistModel::SD_QUALITY_STR);
    decorator.setListFilserProcessor(&proc);

    //when
    int size = decorator.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_HD);
}

void PlaylistModelTest::test_decorateWithHDFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    QualityListFilterProcessor proc;
    proc.setFilterString(PlaylistModel::HD_QUALITY_STR);
    decorator.setListFilserProcessor(&proc);

    //when
    int size = decorator.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_SD);
}

void PlaylistModelTest::test_decorateWithSDHDFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decoratorSD;
    decoratorSD.setParentListModelEntry(&listModelEntry);

    QualityListFilterProcessor procSD;
    procSD.setFilterString(PlaylistModel::SD_QUALITY_STR);
    decoratorSD.setListFilserProcessor(&procSD);

    PlaylistModelEntry entry;
    entry.setTitle("chanal2 HD");
    entry.setQuality("DD");
    entry.setXmltvid("245");

    decoratorSD.append(entry);

    ListModelEntryDecorator decoratorHD;
    decoratorHD.setParentListModelEntry(&decoratorSD);

    QualityListFilterProcessor procHD;
    procHD.setFilterString(PlaylistModel::HD_QUALITY_STR);
    decoratorHD.setListFilserProcessor(&procHD);

    //when
    int size = decoratorHD.size();

    //expected
    QCOMPARE(size,1);
}

void PlaylistModelTest::test_onOffDecorateWithSDFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decorator;
    decorator.setParentListModelEntry(&listModelEntry);

    QualityListFilterProcessor proc;
    proc.setFilterString(PlaylistModel::SD_QUALITY_STR);
    decorator.setListFilserProcessor(&proc);

    //when
    proc.setFilterActive(false);
    int size = decorator.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_HD+ELEMENT_COUNT_SD);

}

void PlaylistModelTest::test_onOffDecorateWithSDHDFilterListModelEntryDecorator()
{
    //given
    ListModelEntry listModelEntry;
    addHDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_HD);
    addSDElementToListOfEntries(listModelEntry,ELEMENT_COUNT_SD);

    ListModelEntryDecorator decoratorSD;
    decoratorSD.setParentListModelEntry(&listModelEntry);

    QualityListFilterProcessor procSD;
    procSD.setFilterString(PlaylistModel::SD_QUALITY_STR);
    decoratorSD.setListFilserProcessor(&procSD);

    PlaylistModelEntry entry;
    entry.setTitle("chanal2 HD");
    entry.setQuality("DD");
    entry.setXmltvid("245");

    decoratorSD.append(entry);

    ListModelEntryDecorator decoratorHD;
    decoratorHD.setParentListModelEntry(&decoratorSD);

    QualityListFilterProcessor procHD;
    procHD.setFilterString(PlaylistModel::HD_QUALITY_STR);
    decoratorHD.setListFilserProcessor(&procHD);

    //when
    procSD.setFilterActive(false);
    int size = decoratorHD.size();

    //expected
    QCOMPARE(size,ELEMENT_COUNT_SD+1);
}

void PlaylistModelTest::addHDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countHD)
{

    for(int i=0;i<countHD;i++){
        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();
        entry.setTitle("chanal HD");
        entry.setQuality("HD");
        entry.setXmltvid("244");
    }

}

void PlaylistModelTest::addHDElementToListOfEntries(ListModelEntry &listEntries, int countHD)
{
    for(int i=0;i<countHD;i++){
        PlaylistModelEntry entry;
        entry.setTitle("chanal HD");
        entry.setQuality("HD");
        entry.setXmltvid("244");
        listEntries.append(entry);
    }
}

void PlaylistModelTest::addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD)
{

    for(int i=0;i<countSD;i++){
        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();
        entry.setTitle("chanal SD");
        entry.setQuality("SD");
        entry.setXmltvid("144");
    }
}

void PlaylistModelTest::addSDElementToListOfEntries(ListModelEntry &listEntries, int countSD)
{
    for(int i=0;i<countSD;i++){
        PlaylistModelEntry entry;
        entry.setTitle("chanal SD");
        entry.setQuality("SD");
        entry.setXmltvid("144");
        listEntries.append(entry);
    }
}

const QVariantMap PlaylistModelTest::createEPG(const QString &jsonStr)
{

    bool ok;
    QVariantMap result = QtJson::Json::parse(jsonStr, ok).toMap();
    QVariantMap epg = result["epg"].toMap();

    return epg;
}

QTEST_APPLESS_MAIN(PlaylistModelTest)

#include "tst_playlistmodeltest.moc"
