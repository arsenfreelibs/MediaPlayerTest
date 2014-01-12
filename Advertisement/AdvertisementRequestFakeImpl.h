#ifndef ADVERTISEMENTREQUESTFAKEIMPL_H
#define ADVERTISEMENTREQUESTFAKEIMPL_H

#include <QUrl>
#include "../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h"


#define FAKE_AD_LINK "http://ytv.su/ad/ad1.mp4"
#define FAKE_BAD_AD_LINK "http://ytv.su/ad/ad_bad.mp4"
#define FAKE_VAST_LINK "[ \"http://ads.adfox.ru/220484/getCode?pp=g&ps=bott&p2=evys&pfc=a&pfb=a&plp=a&pli=a&pop=a\", \"http://h.holder.com.ua/s?b3426&tx&c0&p1&n52d024fb4292e\" ]"
#define FAKE_VAST_LINK_2ND_CORRECT "[ \"http://bad_video_ad.goweb.com/code/bc?referal=123\", \"http://h.holder.com.ua/s?b3426&tx&c0&p1&n52d024fb4292e\" ]"
#define FAKE_VAST_LINK_1ST_PARS_ERROR_2ND_CORRECT "[ \"http://pars_error_ad.goweb.com/code/bc?referal=123\", \"http://h.holder.com.ua/s?b3426&tx&c0&p1&n52d024fb4292e\" ]"
#define FAKE_VAST_BAD_PARS_LINK "http://pars_error_ad.goweb.com/code/bc?referal=123"
#define FAKE_VAST_BAD_VIDEO_LINK "http://bad_video_ad.goweb.com/code/bc?referal=123"
#define FAKE_VAST_BAD_PLAY_LINK "http://ad.goweb.com/code/bc?referal=123"
#define FAKE_AD_START_LINK "http://ad/track-impression"
#define FAKE_AD_BAD_START_LINK "http://ad/track-impression-bad"
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
