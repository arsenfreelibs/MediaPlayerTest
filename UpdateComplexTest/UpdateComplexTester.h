#ifndef UPDATECOMPLEXTESTER_H
#define UPDATECOMPLEXTESTER_H

#include <QObject>
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobImpl.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilderImpl.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.h"
#include "../../../MediaPlayer/src/Network/FileDownloader/UrlDownloader.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateController.h"
#include "../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"
#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManager.h"
#include "../../../MediaPlayer/src/Network/RequestManagerImpl.h"
#include "../../../MediaPlayer/src/Network/RequestManagerConnection.h"
#include "../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"


class UpdateComplexTester : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager networkAccessManager_;
    RequestManagerImpl requestManagerImpl_;
    RequestManagerConnectionImpl requestManagerConnectionImpl_;
    UpdateRequestImpl updateRequest_;
    UserProfile userProfile_;
    FileDownloadListener fileDownloadListener_;
    FileDownloadJobBuilderImpl jobBuilder_;
    FileDownloaderImpl downloader_;
    UpdateControllerImpl updateControllerImpl_;

    UpdateController *updateController_;


public:
    explicit UpdateComplexTester(QObject *parent = 0);
    
signals:
    
public slots:
    void execute();
    void onUpdateExist(const QString &version);
    void onDownloadFinished();
    void onDownloadProgressUpdated(int progress);
    void onDownloadErrorPass(const QString &error);

};

#endif // UPDATECOMPLEXTESTER_H
