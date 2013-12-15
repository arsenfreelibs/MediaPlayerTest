#ifndef ADVERTISEMENTREQUESTFAKEIMPL_H
#define ADVERTISEMENTREQUESTFAKEIMPL_H

#include "../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h"


#define FAKE_AD_LINK "http://ytv.su/ad/ad1.mp4"
#define FAKE_VAST_LINK "http://ad.goweb.com/code/bc?referal=REFERAL_ID"
#define FAKE_VAST_BAD_PLAY_LINK "http://ad.goweb.com/code/bc?referal=123"
#define FAKE_AD_START_LINK "http://ad/track-impression"
#define FAKE_AD_DURATION 30

class AdvertisementRequestFakeImpl : public AdvertisementRequest
{
    Q_OBJECT
public:
    explicit AdvertisementRequestFakeImpl(QObject *parent = 0);
    
signals:
    
public slots:
    virtual void performGetDataRequest(QString url);
    virtual void performStartPlayRequest(QString url);
    virtual void performClickRequest(QString url);
    
};

#endif // ADVERTISEMENTREQUESTFAKEIMPL_H
