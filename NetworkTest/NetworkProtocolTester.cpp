#include "NetworkProtocolTester.h"

NetworkProtocolTester::NetworkProtocolTester(QObject *parent) :
    QObject(parent),countOfTestedEntries_(0),isFinisedTestUrl_(false),isFinisedTestTorrent_(false)
{
    networkRequestManager_.setUserProfile(&userProfile_);

    prepareClassData();
    setSignalSlotConnection();
    prepareReportFile();
    loadSettings();
}

void NetworkProtocolTester::prepareClassData()
{
    urlTestResults_.clear();
    torrentTestResults_.clear();
}

void NetworkProtocolTester::setSignalSlotConnection()
{
    QObject::connect(&userProfile_, SIGNAL(loggedInChanged(bool)),
                     this, SLOT(onLoginStatusChange(bool)));

    QObject::connect(&networkRequestManager_, SIGNAL(channelsListResponseProcessed(std::vector<PlaylistModelEntry>&)),
                     this, SLOT(onChannelsListResponse(std::vector<PlaylistModelEntry>&)));

    QObject::connect(&fileDownloader_, SIGNAL(sendDownloadReportData(QString, QString )),
                     this, SLOT(onSendDownloadReportData(QString, QString )));
    QObject::connect(&fileDownloader_, SIGNAL(finishReportCreation()),
                     this, SLOT(onFinishReportCreation()));

    QObject::connect(&torrentFileDownloader_, SIGNAL(sendDownloadReportData(QString)),
                     this, SLOT(onSendTorrentReportData(QString)));
    QObject::connect(&torrentFileDownloader_, SIGNAL(finishReportCreation()),
                     this, SLOT(onFinishTorrentReportCreation()));
}

void NetworkProtocolTester::prepareReportFile()
{
    file_.setFileName("report.csv");
    file_.open(QIODevice::WriteOnly | QIODevice::Text);
    out_.setDevice(&file_);
    out_ << QString("номер; канал; тест пройден(прямая ссылка); тест пройден(p2p)");
    out_ << "\n";
}

void NetworkProtocolTester::cresteReportFile()
{
    for(int i=0;i<std::min(urlTestResults_.count(),torrentTestResults_.count());i++){
        out_ << urlTestResults_.at(i).toUtf8() << torrentTestResults_.at(i).toUtf8();
        out_ << "\n";
    }

    file_.close();
    qDebug().nospace() << "test finished, close application";
    QCoreApplication::exit(0);
}

void NetworkProtocolTester::loadSettings()
{

    QSettings settings(INI_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup(AUTORISATION_TAG);
    login_ = settings.value(LOGIN_KEY).toString();
    password_ = settings.value(PASSWORD_KEY).toString();
    settings.endGroup();

    settings.beginGroup(TEST_SETTING_TAG);    
    int testing_time = settings.value(TESTING_TIME).toInt();
    int trias_in_second = 4;
    fileDownloader_.setTesting_time(testing_time*trias_in_second);
    torrentFileDownloader_.setTestingTime(testing_time);
    settings.endGroup();

}

void NetworkProtocolTester::execute()
{
    networkRequestManager_.performAuthorizeRequest(login_,password_,true);
}

void NetworkProtocolTester::onLoginStatusChange(bool isLogin)
{
    if(isLogin){
        networkRequestManager_.performChannelsListRequest();
    }
}

void NetworkProtocolTester::onChannelsListResponse(std::vector<PlaylistModelEntry> &entries)
{
    countOfTestedEntries_=0;
    fileDownloader_.downloadAllEntries(entries);
    torrentFileDownloader_.downloadAllEntries(entries);
}

void NetworkProtocolTester::onSendDownloadReportData(QString title, QString status)
{
    countOfTestedEntries_++;
    qDebug().nospace() << "# " << countOfTestedEntries_<< " title = " << title.toUtf8() << "  status = " << status.toUtf8();
    QString num = QString::number(countOfTestedEntries_);
    QString testResult = num.toUtf8() + "; " + title.toUtf8() + "; " + status.toUtf8();
    urlTestResults_.append(testResult);

//    if(urlTestResults_.count()>5){
//        onFinishReportCreation();
//    }
}

void NetworkProtocolTester::onFinishReportCreation()
{
    isFinisedTestUrl_ = true;
    if(isFinisedTestTorrent_){
        cresteReportFile();
    }
}

void NetworkProtocolTester::onSendTorrentReportData(QString status)
{
    QString result = "; " + status.toUtf8();
    torrentTestResults_.append(result);

//    if(torrentTestResults_.count()>5){
//        onFinishTorrentReportCreation();
//    }
}

void NetworkProtocolTester::onFinishTorrentReportCreation()
{
    isFinisedTestTorrent_ = true;
    if(isFinisedTestUrl_){
        cresteReportFile();
    }
}
