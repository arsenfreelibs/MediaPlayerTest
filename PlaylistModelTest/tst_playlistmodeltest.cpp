#include <QString>
#include <QtTest>
#include <../../../MediaPlayer/src/Data/PlaylistModel.h>

class PlaylistModelTest : public QObject
{
    Q_OBJECT
    
private:
    PlaylistModel playlistModel_;

    const int ELEMENT_COUNT_HD = 4;
    const int ELEMENT_COUNT_SD = 3;


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

private:
    void addHDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countHD);
    void addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD);

};

PlaylistModelTest::PlaylistModelTest()
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

void PlaylistModelTest::addHDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countHD)
{

    for(int i=0;i<countHD;i++){
        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();
        entry.setTitle("chanal HD");
        entry.setQuality("HD");
    }

}

void PlaylistModelTest::addSDElementToEntries(std::vector<PlaylistModelEntry> &entries, int countSD)
{

    for(int i=0;i<countSD;i++){
        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();
        entry.setTitle("chanal HD");
        entry.setQuality("SD");
    }
}

QTEST_APPLESS_MAIN(PlaylistModelTest)

#include "tst_playlistmodeltest.moc"
