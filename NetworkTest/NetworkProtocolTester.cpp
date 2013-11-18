#include "NetworkProtocolTester.h"

NetworkProtocolTester::NetworkProtocolTester(QObject *parent) :
    QObject(parent),countOfTestedEntries_(0)
{
    networkRequestManager_.setUserProfile(&userProfile_);

    setSignalSlotConnection();
    prepareReportFile();
    loadSettings();
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
}

void NetworkProtocolTester::prepareReportFile()
{
    file_.setFileName("report.csv");
    file_.open(QIODevice::WriteOnly | QIODevice::Text);
    out_.setDevice(&file_);
    out_ << QString("номер; канал; тест пройден");
    out_ << "\n";    
}

void NetworkProtocolTester::loadSettings()
{

    QSettings settings(INI_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup(AUTORISATION_TAG);
    login_ = settings.value(LOGIN_KEY).toString();
    password_ = settings.value(PASSWORD_KEY).toString();
    settings.endGroup();

    settings.beginGroup(TEST_SETTING_TAG);
    int testing_trias = settings.value(TESTING_TIME).toInt();
    int trias_in_second = 4;
    fileDownloader_.setTesting_time(testing_trias*trias_in_second);
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
}

void NetworkProtocolTester::onSendDownloadReportData(QString title, QString status)
{
    countOfTestedEntries_++;
    qDebug().nospace() << "# " << countOfTestedEntries_<< " title = " << title.toUtf8() << "  status = " << status.toUtf8();
    out_ << countOfTestedEntries_ << "; "<< title.toUtf8() << "; " << status.toUtf8();
    out_ << "\n";
}

void NetworkProtocolTester::onFinishReportCreation()
{
    file_.close();
    qDebug().nospace() << "test finished, close application";
    QCoreApplication::exit(0);
}