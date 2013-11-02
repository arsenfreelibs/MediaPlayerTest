#include "NetworkProtocolTester.h"

NetworkProtocolTester::NetworkProtocolTester(QObject *parent) :
    QObject(parent)
{
    networkRequestManager_.setUserProfile(&userProfile_);

    QObject::connect(&userProfile_, SIGNAL(loggedInChanged(bool)),
                     this, SLOT(onLoginStatusChange(bool)));

    QObject::connect(&networkRequestManager_, SIGNAL(channelsListResponseProcessed(std::vector<PlaylistModelEntry>&)),
                     this, SLOT(onChannelsListResponse(std::vector<PlaylistModelEntry>&)));

    QObject::connect(&fileDownloader_, SIGNAL(sendDownloadReportData(QString, QString )),
                     this, SLOT(onSendDownloadReportData(QString, QString )));
    QObject::connect(&fileDownloader_, SIGNAL(finishReportCreation()),
                     this, SLOT(onFinishReportCreation()));

    prepareReportFile();

}


void NetworkProtocolTester::prepareReportFile()
{
    file_.setFileName("report.csv");
    file_.open(QIODevice::WriteOnly | QIODevice::Text);
    out_.setDevice(&file_);
    out_ << QString("канал; тест пройден");
    out_ << "\n";
}

void NetworkProtocolTester::execute()
{
    networkRequestManager_.performAuthorizeRequest("3816459@i.ua","<fqrfkmcrfz 57,",true);    
}

void NetworkProtocolTester::onLoginStatusChange(bool isLogin)
{
    if(isLogin){
        networkRequestManager_.performChannelsListRequest();
    }
}

void NetworkProtocolTester::onChannelsListResponse(std::vector<PlaylistModelEntry> &entries)
{
    fileDownloader_.downloadAllEntries(entries);
}

void NetworkProtocolTester::onSendDownloadReportData(QString title, QString status)
{
    qDebug().nospace() << "title = " << title << "  status = " << status;
    out_ << title << "; " << status;
    out_ << "\n";
}

void NetworkProtocolTester::onFinishReportCreation()
{
    file_.close();
}
