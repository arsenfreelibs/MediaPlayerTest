#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    requestManagerImpl_.setNetworkAccessManager(&networkAccessManager_);
    requestManagerImpl_.setApiURL("http://dl.goweb.com/api");

    updateRequest_.setRequestManager(&requestManagerImpl_);
    updateRequest_.setRequestManagerConnection(&requestManagerConnectionImpl_);

    downloader_.setJobBuilder(&jobBuilder_);

    updateControllerImpl_.setUpdateRequest(&updateRequest_);
    updateControllerImpl_.setUserProfile(&userProfile_);
    QString ver_app = APP_VERSION;
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
    QObject::connect(updateController_, SIGNAL(downloadErrorPass(const QString &)),
                     this, SLOT(onDownloadErrorPass(const QString &)));


    ui->setupUi(this);

    QTimer::singleShot(100, this, SLOT(downloadNewVersion()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadNewVersion()
{
    userProfile_.setLoggedIn(true); //must call updateController->checkAvailableUpdate();
}

void MainWindow::onUpdateExist(const QString &version)
{
    ui->label->setText("Downloading GoWebMediaPlayer ver. " + version);
    updateController_->downloadNewVersion();
}

void MainWindow::onDownloadFinished()
{
    // Not emited when downloading is stoped, in this case would be emited error signal
    qDebug().nospace() << "---[UpdateComplexTester::onDownloadFinished]------------Download finisen ok";

    updateController_->installDownloadedNewVersion();
}

void MainWindow::onDownloadProgressUpdated(int progress)
{
    qDebug().nospace() << "---[UpdateComplexTester::downloadProgressUpdated]------------progress = " <<progress;
    ui->progressBar->setValue(progress);
}

void MainWindow::onDownloadErrorPass(const QString &error)
{
    qDebug().nospace() << "---[UpdateComplexTester::onDownloadErrorPass]------------Download aborted or occure error during downloading, error = "<<error;
    QCoreApplication::exit();
}

void MainWindow::on_pushButton_clicked()
{
    updateController_->stopDownloadNewVersion();
}
