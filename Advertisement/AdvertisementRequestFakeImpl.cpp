#include "AdvertisementRequestFakeImpl.h"

AdvertisementRequestFakeImpl::AdvertisementRequestFakeImpl(QObject *parent) :
    AdvertisementRequest(parent)
{
}

void AdvertisementRequestFakeImpl::performGetDataRequest(QString url)
{
    AdvertisementRequest::AdData adData;

    if(url == ""){
        emit finishedGetData(adData,AdvertisementRequest::StatusNetworkFailure);
        return;
    }

    if(url == FAKE_VAST_BAD_PARS_LINK){
        adData.videoUrl = "";
        adData.startUrl = "";
        adData.duration = 0;
        emit finishedGetData(adData,AdvertisementRequest::StatusParseFailure);
        return;
    }

    if(url == FAKE_VAST_BAD_VIDEO_LINK){
        adData.videoUrl = "";
        adData.startUrl = "";
        adData.duration = 0;
        emit finishedGetData(adData,AdvertisementRequest::StatusSuccess);
        return;
    }

    QUrl urlObj(url);
    if(urlObj.isValid()){        
        if(url == FAKE_VAST_BAD_PLAY_LINK){
            adData.videoUrl = FAKE_BAD_AD_LINK;
            adData.startUrl = FAKE_AD_BAD_START_LINK;
            adData.duration = 0;
            emit finishedGetData(adData,AdvertisementRequest::StatusSuccess);
            return;
        }

        adData.videoUrl = FAKE_AD_LINK;
        adData.startUrl = FAKE_AD_START_LINK;
        adData.duration = FAKE_AD_DURATION;
        emit finishedGetData(adData,AdvertisementRequest::StatusSuccess);
        return;
    }

    adData.videoUrl = "";
    adData.startUrl = "";
    adData.duration = 0;
    emit finishedGetData(adData,AdvertisementRequest::StatusNetworkFailure);
}

void AdvertisementRequestFakeImpl::performStartPlayRequest(QString url)
{
    if(url == FAKE_AD_BAD_START_LINK){
        emit finishedRqstToStartingPlay(AdvertisementRequest::StatusNetworkFailure);
        return;
    }
    emit finishedRqstToStartingPlay(AdvertisementRequest::StatusSuccess);
}

void AdvertisementRequestFakeImpl::performClickRequest(QString url)
{
}
