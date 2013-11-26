#ifndef NETWORKPROTOCOLTESTER_H
#define NETWORKPROTOCOLTESTER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include<algorithm>
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"
#include "FileDownloader.h"
#include "TorrentFileDownloader.h"

#define INI_FILE_NAME "test.ini"
#define AUTORISATION_TAG "AUTORISATION_TAG"
#define LOGIN_KEY "login"
#define PASSWORD_KEY "password"

#define TEST_SETTING_TAG "TEST_SETTING_TAG"
#define TESTING_TIME "test_time"

class NetworkProtocolTester : public QObject
{
    Q_OBJECT

private:
    NetworkRequestManager networkRequestManager_;
    UserProfile userProfile_;
    FileDownloader fileDownloader_;
    TorrentFileDownloader torrentFileDownloader_;

    QFile file_;
    QTextStream out_;

    QString login_;
    QString password_;

    int countOfTestedEntries_;

    QList<QString> urlTestResults_;
    QList<QString> torrentTestResults_;

    bool isFinisedTestUrl_;
    bool isFinisedTestTorrent_;

public:
    explicit NetworkProtocolTester(QObject *parent = 0);
    
signals:
    
public slots:
    void execute();

    void onLoginStatusChange(bool isLogin);
    void onChannelsListResponse(std::vector<PlaylistModelEntry> &entries);
    void onSendDownloadReportData(QString title, QString status);
    void onFinishReportCreation();
    void onSendTorrentReportData(QString status);
    void onFinishTorrentReportCreation();

private:
    void prepareClassData();
    void loadSettings();
    void setSignalSlotConnection();
    void prepareReportFile();
    void cresteReportFile();
    
};

#endif // NETWORKPROTOCOLTESTER_H
