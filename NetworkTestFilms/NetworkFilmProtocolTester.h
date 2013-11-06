#ifndef NETWORKFILMPROTOCOLTESTER_H
#define NETWORKFILMPROTOCOLTESTER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"
#include "NetworkFileRequestManager.h"
#include "FileFilmDownloader.h"

#define INI_FILE_NAME "test.ini"
#define AUTORISATION_TAG "AUTORISATION_TAG"
#define LOGIN_KEY "login"
#define PASSWORD_KEY "password"

#define TEST_SETTING_TAG "TEST_SETTING_TAG"
#define TESTING_TIME "test_time"

class NetworkFilmProtocolTester : public QObject
{
    Q_OBJECT
private:
    NetworkFileRequestManager networkRequestManager_;
    UserProfile userProfile_;
    FileFilmDownloader fileDownloader_;

    QFile file_;
    QTextStream out_;

    QString login_;
    QString password_;

    int countOfTestedEntries_;


public:
    explicit NetworkFilmProtocolTester(QObject *parent = 0);

signals:

public slots:
    void execute();

    void onLoginStatusChange(bool isLogin);
    void onFilmsListResponse(std::vector<PlaylistModelEntry> &entries);
    void onSendDownloadReportData(QString title, QString status);
    void onFinishReportCreation();

private:
    void loadSettings();
    void setSignalSlotConnection();
    void prepareReportFile();
    
};

#endif // NETWORKFILMPROTOCOLTESTER_H
