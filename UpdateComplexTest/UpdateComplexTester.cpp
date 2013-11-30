#include "UpdateComplexTester.h"

UpdateComplexTester::UpdateComplexTester(QObject *parent) :
    QObject(parent)
{

    requestManagerImpl_.setNetworkAccessManager(&networkAccessManager_);
    requestManagerImpl_.setApiURL("http://dl.goweb.com/api");

    updateRequest_.setRequestManager(&requestManagerImpl_);
    updateRequest_.setRequestManagerConnection(&requestManagerConnectionImpl_);

    downloader_.setJobBuilder(&jobBuilder_);

    updateControllerImpl_.setUpdateRequest(&updateRequest_);
    updateControllerImpl_.setUserProfile(&userProfile_);
    QString ver_app = VERSION_APP;
    updateControllerImpl_.setVersion(ver_app);
    updateControllerImpl_.setFileDownloadListener(&fileDownloadListener_);
    updateControllerImpl_.setFileDownloader(&downloader_);

    updateController_ = &updateControllerImpl_;


    QObject::connect(updateController_, SIGNAL(updateExist(const QString &)),
                     this, SLOT(onUpdateExist(const QString &)));

    QObject::connect(updateController_, SIGNAL(downloadFinished()),
                     this, SLOT(onDownloadFinished()));
    QObject::connect(updateController_, SIGNAL(downloadProgressUpdated(int)),
                     this, SLOT(onDownloadProgressUpdated(int)));

}

void UpdateComplexTester::execute()
{
    userProfile_.setLoggedIn(true); //must call updateController->checkAvailableUpdate();
}

void UpdateComplexTester::onUpdateExist(const QString &version)
{
    updateController_->downloadNewVersion();
}

void UpdateComplexTester::onDownloadFinished()
{
    qDebug().nospace() << "---[UpdateComplexTester::onDownloadFinished]------------Download finisen ok";
}

void UpdateComplexTester::onDownloadProgressUpdated(int progress)
{
    qDebug().nospace() << "---[UpdateComplexTester::downloadProgressUpdated]------------progress = " <<progress;
}
