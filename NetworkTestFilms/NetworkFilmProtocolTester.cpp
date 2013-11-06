#include "NetworkFilmProtocolTester.h"

NetworkFilmProtocolTester::NetworkFilmProtocolTester(QObject *parent) :
    QObject(parent)
{    
    networkRequestManager_.setUserProfile(&userProfile_);

    setSignalSlotConnection();
    prepareReportFile();
    loadSettings();
}

void NetworkFilmProtocolTester::setSignalSlotConnection()
{
    QObject::connect(&userProfile_, SIGNAL(loggedInChanged(bool)),
                     this, SLOT(onLoginStatusChange(bool)));

    QObject::connect(&networkRequestManager_, SIGNAL(filmsListResponseProcessed(std::vector<PlaylistModelEntry>&)),
                     this, SLOT(onFilmsListResponse(std::vector<PlaylistModelEntry>&)));

    QObject::connect(&fileDownloader_, SIGNAL(sendDownloadReportData(QString, QString )),
                     this, SLOT(onSendDownloadReportData(QString, QString )));
    QObject::connect(&fileDownloader_, SIGNAL(finishReportCreation()),
                     this, SLOT(onFinishReportCreation()));
}

void NetworkFilmProtocolTester::prepareReportFile()
{
    file_.setFileName("report.csv");
    file_.open(QIODevice::WriteOnly | QIODevice::Text);
    out_.setDevice(&file_);
    out_ << QString("номер; канал; тест пройден");
    out_ << "\n";
}

void NetworkFilmProtocolTester::loadSettings()
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

void NetworkFilmProtocolTester::execute()
{
    networkRequestManager_.performAuthorizeRequest(login_,password_,true);
}

void NetworkFilmProtocolTester::onLoginStatusChange(bool isLogin)
{
    if(isLogin){
        countOfTestedEntries_=0;
        networkRequestManager_.performFilmsListRequest(0);
    }
}

void NetworkFilmProtocolTester::onFilmsListResponse(std::vector<PlaylistModelEntry> &entries)
{    
    fileDownloader_.downloadAllEntries(entries);
}

void NetworkFilmProtocolTester::onSendDownloadReportData(QString title, QString status)
{
    countOfTestedEntries_++;
    qDebug().nospace() << "# " << countOfTestedEntries_<< " title = " << title.toUtf8() << "  status = " << status.toUtf8();
    out_ << countOfTestedEntries_ << "; "<< title.toUtf8() << "; " << status.toUtf8();
    out_ << "\n";
}

void NetworkFilmProtocolTester::onFinishReportCreation()
{
    networkRequestManager_.performFilmsListRequest(countOfTestedEntries_);
//    file_.close();
//    qDebug().nospace() << "test finished, close application";
//    QCoreApplication::exit(0);
}
