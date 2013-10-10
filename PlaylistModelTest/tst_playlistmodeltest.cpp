#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Data/PlaylistModel.h>
#include <../../../MediaPlayer/src/qt-json/json.h>

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
    void test_rowCount_noHD_noSD();
    void test_rowCount_HD_noSD();
    void test_rowCount_noHD_SD();
    void test_rowCount_HD_SD();
    void test_populate();
    void test_removeAllEntries();
    void test_rowCount_after_removeAllEntries();
    void test_loadProgramInfoFromMap();
    void test_loadProgramInfoFromMap_with_sameStartTime();

private:
    void addHDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countHD);
    void addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD);
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

void PlaylistModelTest::addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD)
{

    for(int i=0;i<countSD;i++){
        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();
        entry.setTitle("chanal HD");
        entry.setQuality("SD");
        entry.setXmltvid("144");
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
