#include <math.h>
#include <iostream>
//#include <windows.h>

#include <QDebug>
#include <QScreen>
//#include <QCursor>
//#include <QWindow>
//#include <QQuickView>
//#include <QQuickWindow>
//#include <QTimer>
//#include <QPoint>
//#include <QGuiApplication>
//#include <qpa/qplatformnativeinterface.h>
//#include <QPropertyAnimation>

#include "VLCPlayer.h"
//#include "VLCPlayerWindow.h"
//#include "VLCMouseHook.h"

#define LOGGING 0
#define LOGGING_VLC 0

#define COMMENT_THINGS_OFF

const int VLCPlayer::mouseActivityIntervalMsecs = 1000;
//libvlc_media_list_player_t *media_list_player;

libvlc_event_type_t VLCPlayer::eventTypesToSubscribe[] = {
    //    libvlc_MediaMetaChanged,
    //    libvlc_MediaSubItemAdded,
    //    libvlc_MediaDurationChanged,
    //    libvlc_MediaParsedChanged,
    //    libvlc_MediaFreed,
    //    libvlc_MediaStateChanged,
    libvlc_MediaPlayerMediaChanged,
    //    libvlc_MediaPlayerNothingSpecial,
    //    libvlc_MediaPlayerOpening,
    //    libvlc_MediaPlayerBuffering,
    libvlc_MediaPlayerPlaying,
    libvlc_MediaPlayerPaused,
    libvlc_MediaPlayerStopped,
    //    libvlc_MediaPlayerForward,
    //    libvlc_MediaPlayerBackward,
    libvlc_MediaPlayerEndReached,
    libvlc_MediaPlayerEncounteredError,
    libvlc_MediaPlayerTimeChanged,
    libvlc_MediaPlayerPositionChanged,
    //    libvlc_MediaPlayerSeekableChanged,
    libvlc_MediaPlayerPausableChanged,
    //    libvlc_MediaPlayerTitleChanged,
    //    libvlc_MediaPlayerSnapshotTaken,
    libvlc_MediaPlayerLengthChanged,
    //    libvlc_MediaPlayerVout,
    //    libvlc_MediaListItemAdded,
    //    libvlc_MediaListWillAddItem,
    //    libvlc_MediaListItemDeleted,
    //    libvlc_MediaListWillDeleteItem,
    //    libvlc_MediaListViewItemAdded,
    //    libvlc_MediaListViewWillAddItem,
    //    libvlc_MediaListViewItemDeleted,
    //    libvlc_MediaListViewWillDeleteItem,
    //    libvlc_MediaListPlayerPlayed,
    //    libvlc_MediaListPlayerNextItemSet,
    //    libvlc_MediaListPlayerStopped,
    //    libvlc_MediaDiscovererStarted,
    //    libvlc_MediaDiscovererEnded,
    //    libvlc_VlmMediaAdded,
    //    libvlc_VlmMediaRemoved,
    //    libvlc_VlmMediaChanged,
    //    libvlc_VlmMediaInstanceStarted,
    //    libvlc_VlmMediaInstanceStopped,
    //    libvlc_VlmMediaInstanceStatusInit,
    //    libvlc_VlmMediaInstanceStatusOpening,
    //    libvlc_VlmMediaInstanceStatusPlaying,
    //    libvlc_VlmMediaInstanceStatusPause,
    //    libvlc_VlmMediaInstanceStatusEnd,
    //    libvlc_VlmMediaInstanceStatusError
};

libvlc_event_type_t VLCPlayer::mediaListEventTypesToSubscribe[] = {
    libvlc_MediaListItemAdded,
    libvlc_MediaListWillAddItem,
};

libvlc_event_type_t VLCPlayer::acestreamEventTypesToSubscribe[] = {
    libvlc_AcestreamError,
    libvlc_AcestreamStatus,
    libvlc_AcestreamState,
    libvlc_AcestreamStatusRaw,
    libvlc_AcestreamShowUserDataDialog
};

VLCPlayer::VLCPlayer(QObject *parent)
    : QObject(parent)
    , mediaPlayerAttachedToSystemWindow_(false)
    , shown_(false)
    , panelShown_(false)
//    , window_(NULL)
//    , panelWindow_(NULL)
    , fullscreen_(false)
    , windowWasMaximized_(false)
//    , lastMouseActivityMoment_(QDateTime::currentDateTimeUtc())
//    , lastKnownMousePosition_(0, 0)
    , vlcInstance_(NULL)
    , mediaPlayer_(NULL)
    , media_(NULL)
    , eventManager_(NULL)
    , shouldPauseOnPlayActuating_(false)
{
    // Initialize an instance of vlc
    const char *args[] = {
        "--no-video-title","--ace-developer-key=wEO4BLR3OBLx8uaq7-bSHEMTp5zM-Q5b1y7qsrqSlL4A-sJ5qElK7T",
        "--intf=dummy","--no-media-library","--no-video-title-show"
    #if LOGGING_VLC
        , "--verbose", "2"
    #endif
    };

    vlcInstance_ = libvlc_new(sizeof(args)/sizeof(args[0]), args);
    if (!vlcInstance_)
        reportError();

#ifdef LOGGING
    std::cout << "libvlc version: " << libvlc_get_version() << std::endl;
#endif

    // Create a media player playing environement
    mediaPlayer_ = libvlc_media_player_new(vlcInstance_);
    if (!mediaPlayer_)
        reportError();



    //new player
    media_list = libvlc_media_list_new(vlcInstance_);

    // !!! Обязательно использование libvlc_media_list_player_t, так как он выполняет команду старт
    media_list_player = libvlc_media_list_player_new(vlcInstance_);
    acestream = libvlc_acestream_object_new(vlcInstance_);

    // Связываем  media_list_player с списком воспроизведения и плеером ...
    libvlc_media_list_player_set_media_list(media_list_player, media_list);
    libvlc_media_list_player_set_media_player(media_list_player, mediaPlayer_);

    // ... и libvlc_acestream_object с media_list_player-ом
    libvlc_acestream_object_set_media_list_player(acestream, media_list_player);

    eventManager_acestream_ = libvlc_acestream_object_event_manager(acestream);

    eventManager_MediaList_ = libvlc_media_list_event_manager(media_list);

    eventManager_ = libvlc_media_player_event_manager(mediaPlayer_);
    if (!eventManager_)
        reportError();

    subscribeToEvents();
    subscribeToMediaListEvents();
    subscribeToAcestreamEvents();

//    createNativeWindow();

//    updateElapsedTimeUTCTimer_ = new QTimer(this);
//    updateElapsedTimeUTCTimer_->setSingleShot(false);
//    updateElapsedTimeUTCTimer_->setInterval(1000);
//    QObject::connect(updateElapsedTimeUTCTimer_, SIGNAL(timeout()),
//                     this, SLOT(updateElapsedTimeUTC()));
//    updateElapsedTimeUTCTimer_->start();


//    mouseTrackTimer_ = new QTimer(this);
//    mouseTrackTimer_->setSingleShot(false);
//    mouseTrackTimer_->setInterval(200);

//    QObject::connect(mouseTrackTimer_, SIGNAL(timeout()),
//                     this, SLOT(checkMouseActivity()));
//    // VLC can create additional child window at any moment (for example,
//    // after issuing Play command), so update mouse hook on every VLC event
//    //QObject::connect(this, SIGNAL(playingChanged()), // does not work as intended :( window is created with delay after clicking Play
//    //				 this, SLOT(updateMouseHook()));
//    //QObject::connect(this, SIGNAL(vlcEvent()), // subscribe to all events to catch window appearing. hack. finally decided to use timer instead
//    //				 this, SLOT(updateMouseHook()));
//    hookUpdateTimer_ = new QTimer(this);
//    hookUpdateTimer_->setSingleShot(false);
//    hookUpdateTimer_->setInterval(200);
//    QObject::connect(hookUpdateTimer_, SIGNAL(timeout()),
//                     this, SLOT(updateMouseHook()));

//    QObject::connect(VLCMouseHook::sharedInstance(), SIGNAL(doubleClicked()),
//                     this, SLOT(doubleClickHookTriggered()));
//    QObject::connect(this, SIGNAL(playingChanged()),
//                     this, SLOT(onPlayingChanged()));
}

VLCPlayer::~VLCPlayer()
{
    /* Stop playing */
    if (mediaPlayer_)
        libvlc_media_player_stop(mediaPlayer_);

    //if (mouseHook_) FIXME
    //    UnhookWindowsHookEx(mouseHook_);

//    unsubscribeFromEvents();

    if (media_)
        libvlc_media_release(media_);

    /* Free the media_player */
    if (mediaPlayer_)
        libvlc_media_player_release(mediaPlayer_);

    if (vlcInstance_)
        libvlc_release(vlcInstance_);
}

//void VLCPlayer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
//{
//    QQuickItem::geometryChanged(newGeometry, oldGeometry);

//#if 0
//    if (/*!windowHandle_ && */!createNativeWindow())
//    {
//#if LOGGING
//        qDebug() << "No window handle";
//#endif
//        return;
//    }
//#else
//    if (!window_)
//        return;
//#endif

//    if (!fullscreen_)
//    {
//        QPointF globalOrigin = localToWindow(0, 0);
//        window_->setGeometry(globalOrigin.x(),
//                             globalOrigin.y(),
//                             newGeometry.width(),
//                             newGeometry.height());
//    }

//    if (!panelWindow_)
//        return;

//    panelWindow_->setGeometry(0,
//                              window_->height() - panelWindow_->height(),
//                              window_->width(),
//                              panelWindow_->height());
//}

//bool VLCPlayer::playing() const
//{
//    return (bool)libvlc_media_player_is_playing(mediaPlayer_);
//}

//qint64 VLCPlayer::mediaLength() const
//{
//    if (!mediaPlayer_)
//        return 0;

//    qint64 length = libvlc_media_player_get_length(mediaPlayer_);
//    if (length == -1) // There is no media
//        return 0;
//    return length;
//}

//qint64 VLCPlayer::time() const
//{
//    if (!mediaPlayer_)
//        return 0;

//    qint64 time = libvlc_media_player_get_time(mediaPlayer_);
//    if (time == -1) // There is no media
//        return 0;
//    return time;
//}

//float VLCPlayer::position() const
//{
//    if (!mediaPlayer_)
//        return 0;

//    float pos = libvlc_media_player_get_position(mediaPlayer_);
//    if (pos == -1) // There is no media
//        return 0;
//    return pos;
//}

//bool VLCPlayer::pausable() const
//{
//    if (!mediaPlayer_)
//        return 0;

//    return libvlc_media_player_can_pause(mediaPlayer_);
//}

//QString VLCPlayer::aspectRatio() const
//{
//    if (!mediaPlayer_)
//        return QString();
//    char *ratio = libvlc_video_get_aspect_ratio(mediaPlayer_);
//    if (!ratio)
//    {
//        // Aspect ratio is unspecified
//        return QString();
//    }
//    QString result(ratio);
//    free(ratio);
//    return result;
//}

//bool VLCPlayer::widescreen() const
//{
//    return aspectRatio() == "16:9";
//}

//float VLCPlayer::volume() const
//{
//    if (!mediaPlayer_)
//        return 0;

//    // FIXME non-linear volume
//    return libvlc_audio_get_volume(mediaPlayer_) / 100.0;
//}

//bool VLCPlayer::isTVStream() const
//{
//    if (!mediaPlayer_)
//        return false;
//    return isTVStream_;
//}

//int VLCPlayer::totalTimeUTC() const
//{
//    if (!mediaPlayer_)
//        return 0;
//    return totalTimeUTC_;
//}

//int VLCPlayer::elapsedTimeUTC() const
//{
//    if (!mediaPlayer_)
//        return 0;
//    return elapsedTimeUTC_;
//}

//bool VLCPlayer::muted() const
//{
//    if (!mediaPlayer_)
//        return false;
//    return (bool)libvlc_audio_get_mute(mediaPlayer_);
//}

//void VLCPlayer::show()
//{
//    if (!window_)
//        return;

//    if (shown_)
//        return;

//    QWindow *topLevelWindow = window();
//    window_->showNormal();
//    //	panelWindow_->showNormal();
//    if (topLevelWindow->windowState() == Qt::WindowFullScreen)
//        topLevelWindow->show(); // Call show() instead of showNormal() to keep default showing mode

//    updateMouseHook();
//    hookUpdateTimer_->start();

//    setShown(true);
//}

//void VLCPlayer::hide()
//{
//    if (!window_)
//        return;

//    if (!shown_)
//        return;

//    setFullscreen(false);
//    //	hidePanel(); // Not neccessary
//    window_->hide();
//    qDebug() << "unhook(): VLCPlayer" << this;
//    hookUpdateTimer_->stop();
//    VLCMouseHook::sharedInstance()->unhook();

//    setShown(false);
//}

//void VLCPlayer::doubleClickHookTriggered()
//{
//    if (!shown_)
//        return;
//    emit doubleClicked();
//}

//void VLCPlayer::playURL(const QString &url, const QString &title)
//{
//    //    LOG("playUrl='%s'", url.toLocal8Bit().data());

//    //if (!mediaPlayerAttachedToSystemWindow_) // done in performPlay
//    //	return;

//    qDebug() << "playUrl" << url << "\n";
//    setSource(url);
//    setTitle(title);
//    CreateNewLibVlcMediaDescriptor(source_);
//    //    libvlc_media_player_play(mediaPlayer_);
//    performPlay();

//}

void VLCPlayer::playTorrentURL(const QString &url, const QString &title)
{
    QByteArray ba = url.toLocal8Bit();
    const char *c_url = ba.data();

    libvlc_acestream_object_load(acestream,
                                 c_url,
                                 NULL,
                                 libvlc_ace_id_type_TorrentUrl,
                                 libvlc_ace_load_Async,
                                 NULL,
                                 0, 0, 0);
}

//void VLCPlayer::playAvailableURL(const QString &url, const QString &torrentUrl, const QString &title)
//{
//    setSource(url);
//    setTitle(title);
//    if(torrentUrl.length()>0){
//        playTorrentURL(torrentUrl, title);
//    }
//    else{
//        libvlc_acestream_object_stop(acestream);
//        //        playURL(url,title);
//    }
//    CreateNewLibVlcMediaDescriptor(source_);
//    performPlay();
//}

//void VLCPlayer::setSource(const QString &source)
//{
//    if (source_ == source)
//        return;

//    source_ = source;
//    emit sourceChanged();
//}
//void VLCPlayer::CreateNewLibVlcMediaDescriptor(const QString &source){
//    // FIXME: release media_
//    if (media_)
//        libvlc_media_release(media_);
//    media_ = libvlc_media_new_location(vlcInstance_, source.toLocal8Bit().data(), "");
//    if (!media_)
//        reportError();
//}

//void VLCPlayer::setTitle(const QString &title)
//{
//    if (title_ == title)
//        return;

//    Q_ASSERT(panelWindow_);
//    if (panelWindow_)
//    {
//        title_ = title;
//        QQuickItem *panel = panelWindow_->rootObject();
//        Q_ASSERT(panel);
//        panel->setProperty("movieTitle", title_);
//        emit titleChanged();
//    }
//    else
//    {
//        qWarning() << "No panel window";
//    }
//}

void VLCPlayer::setStatus(const QString &status)
{
    status_ = status;
    emit statusChanged(status_);
    //    emit titleChanged();
}

void VLCPlayer::setStatusRaw(const QString &status)
{
    statusRaw_ = status;
}

//void VLCPlayer::play()
//{
//    if (!mediaPlayerAttachedToSystemWindow_)
//        return;

//    if (mediaPlayer_ && !playing())
//    {
//        emit sourceChanged();

//        libvlc_media_player_play(mediaPlayer_);
//        // Try to workaround ocassional freeze bug by delaying
//        // mouse hook rebinding to new hwnd:
//        hookUpdateTimer_->stop();
//        hookUpdateTimer_->start();
//        //		emit playingChanged(true);
//    }
//}

void VLCPlayer::playMedia()
{
    if (media_list_player)
    {
        //libvlc_media_list_player_play(media_list_player);
        libvlc_media_list_player_next(media_list_player);
    }

}

//void VLCPlayer::pause()
//{
//    if (!mediaPlayerAttachedToSystemWindow_)
//        return;

//    if (mediaPlayer_ )
//    {
//        if (playing())
//            libvlc_media_player_pause(mediaPlayer_);
//        else
//            shouldPauseOnPlayActuating_ = true;
//    }
//}

//void VLCPlayer::stop()
//{
//    if (!mediaPlayerAttachedToSystemWindow_)
//        return;

//    if (mediaPlayer_)
//    {
//        libvlc_media_player_stop(mediaPlayer_);
//        // Try to workaround ocassional freeze bug by delaying
//        // mouse hook rebinding to new hwnd:
//        hookUpdateTimer_->stop();
//        hookUpdateTimer_->start();
//    }
//}

//void VLCPlayer::setTime(qint64 time)
//{
//    if (!mediaPlayer_)
//        return;
//    libvlc_media_player_set_time(mediaPlayer_, time);
//    if (!playing())
//    {
//        // When paused, VLC does not notify on position change,
//        // so do this manually.
//        emit timeChanged();
//        emit positionChanged();
//    }
//}

//void VLCPlayer::setPosition(float position)
//{
//    if (!mediaPlayer_)
//        return;
//    libvlc_media_player_set_position(mediaPlayer_, position);
//    if (!playing())
//    {
//        // When paused, VLC does not notify on position change,
//        // so do this manually.
//        emit timeChanged();
//        emit positionChanged();
//    }
//}

//void VLCPlayer::setAspectRatio(const QString &aspectRatio)
//{
//    if (!mediaPlayer_)
//        return;
//    if (this->aspectRatio() == aspectRatio)
//        return;

//    bool wasWidescreen = widescreen();

//    if (aspectRatio.isEmpty())
//        libvlc_video_set_aspect_ratio(mediaPlayer_, NULL);
//    else
//        libvlc_video_set_aspect_ratio(mediaPlayer_, aspectRatio.toUtf8().data());

//    emit aspectRatioChanged();
//    if (wasWidescreen != widescreen())
//        emit widescreenChanged();
//}

//void VLCPlayer::setWidescreen(bool widescreen)
//{
//    if (!mediaPlayer_)
//        return;
//    bool aspectRatioIsWidescreen = this->widescreen();
//    if (widescreen == aspectRatioIsWidescreen)
//        return;
//    setAspectRatio(widescreen ? "16:9" : "");
//}

//void VLCPlayer::setVolume(float volume)
//{
//    if (!mediaPlayer_)
//        return;

//    // FIXME non-linear volume
//    int internalLevel = (int)round(volume * 100);
//    //	int internalLevel = (int)round(volume*volume*volume*volume*100);
//    //	qDebug() << "SET VOLUME LEVEL:" << volume;
//    //	qDebug() << "SET VOLUME INTERNAL LEVEL:" << internalLevel;
//    if (-1 == libvlc_audio_set_volume(mediaPlayer_, internalLevel))
//    {
//        Q_ASSERT_X(false, "VLCPlayer::setVolume", "Volume level is out of range");
//        return;
//    }
//    emit volumeChanged();
//}

//void VLCPlayer::setMuted(bool muted)
//{
//    if (!mediaPlayer_)
//        return;
//    libvlc_audio_set_mute(mediaPlayer_, (int)muted);
//    emit mutedChanged();
//}

//void VLCPlayer::setIsTVStream(bool isTVstream)
//{
//    if (!mediaPlayer_)
//        return;
//    isTVStream_ = isTVstream;
//    emit isTVStreamChanged();
//}

//void VLCPlayer::setTotalTimeUTC(int totalTimeUTC)
//{
//    if (!mediaPlayer_)
//        return;
//    totalTimeUTC_ = totalTimeUTC;
//    emit totalTimeUTCChanged();
//}


//void VLCPlayer::setElapsedTimeUTC(int elapsedTimeUTC)
//{
//    if (!mediaPlayer_)
//        return;
//    elapsedTimeUTC_ = elapsedTimeUTC;
//    emit elapsedTimeUTCChanged();
//}
//void VLCPlayer::toggleMute()
//{
//    if (!mediaPlayer_)
//        return;
//    libvlc_audio_toggle_mute(mediaPlayer_);
//}

//void VLCPlayer::setFullscreen(bool fullscreen)
//{
//    if (fullscreen_ == fullscreen)
//        return;

//    fullscreen_ = fullscreen;

//    if (!shown_)
//        return;

//    qDebug() << "setFullscreen(" << fullscreen << ")";

//    QQuickWindow *topLevelWindow = this->window();
//    if (!topLevelWindow)
//        return;

//    if (fullscreen_)
//    {
//        windowWasMaximized_ =
//                topLevelWindow->windowState() == Qt::WindowMaximized;
//        topLevelWindow->showFullScreen();
//        window_->showFullScreen();
//        //		window_->showMaximized();

//        panelWindow_->setVisible(true);
//        showPanel();
//        lastMouseActivityMoment_ = QDateTime::currentDateTimeUtc();
//        lastKnownMousePosition_ = QCursor::pos();
//        mouseTrackTimer_->start();
//    }
//    else
//    {
//        if (windowWasMaximized_)
//            topLevelWindow->showMaximized();
//        else
//            topLevelWindow->show();
//        window_->showNormal();
//        hidePanel();
//        panelWindow_->setVisible(false);

//        mouseTrackTimer_->stop();
//    }

//    emit fullscreenChanged();
//}

//bool VLCPlayer::createNativeWindow()
//{
//    // Assume that VLC instance is already created when this
//    // function is called.

//#if LOGGING
//    qDebug() << "createNativeWindow";
//#endif

//    if (window_)
//        return true;

//    /*
//    QGuiApplication *app = static_cast<QGuiApplication *>(
//                QGuiApplication::instance());
//    QWindow *topWindow = NULL;
//    foreach (QWindow *window, app->allWindows())
//    {
//        if (!window)
//            continue;
//        topWindow = window;
//        break;
//    }
//*/
//    QWindow *topWindow = window();
//    if (topWindow)
//    {
//        HWND parentHwnd = getHWNDForWindow(topWindow);
//        if (parentHwnd)
//        {
//            QPointF globalOrigin = localToWindow(0, 0);

//            window_ = new VLCPlayerWindow(topWindow);
//            window_->setClearBeforeRendering(true);
//            window_->setColor(QColor(0, 0, 0));
//            window_->setX(globalOrigin.x());
//            window_->setY(globalOrigin.y());
//            window_->setWidth(width());
//            window_->setHeight(height());

//            panelWindow_ = new VLCPlayerWindow(window_);
//            panelWindow_->setObjectName("VLCPlayerPanelWindow");
//            panelWindow_->setSource(QUrl("qml/MediaPlayer/Controls/Player/Fullscreen/PlayerFullscreenDashboard.qml"));
//            panelWindow_->setResizeMode(QQuickView::SizeRootObjectToView);
//            panelWindow_->setClearBeforeRendering(true);
//            panelWindow_->setColor(QColor(0, 0, 0));
//            panelWindow_->setFlags(/*Qt::FramelessWindowHint |*/ Qt::ToolTip);
//            QQuickItem *panel = panelWindow_->rootObject();
//            qDebug() << "PLAYER DASHBOARD:" << panel;
//            panel->setProperty("player", QVariant::fromValue<VLCPlayer *>(this));
//            //			panel->setProperty("anchors.left", );
//            //			panel->setProperty("anchors.right", "parent.right");

//            panelWindow_->setResizeMode(QQuickView::SizeRootObjectToView);

//            // When player is in fullscreen mode, the panel
//            // is always visible (in terms of window system)
//            // and is hidden/shown to user by adjusting
//            // it's Y co-ordinate.
//            QObject::connect(window_, SIGNAL(widthChanged(int)),
//                             this, SLOT(updatePanelWidth()));
//        }
//    }

//    if (!window_)
//    {
//        QTimer::singleShot(100, this, SLOT(createNativeWindow()));
//        return false;
//    }

//    attachHWND();

//    return true;
//}

//bool VLCPlayer::attachHWND()
//{
//    HWND hwnd = getHWNDForWindow(window_);
//    if (!hwnd || !mediaPlayer_)
//    {
//        QTimer::singleShot(100, this, SLOT(attachHWND()));
//        return false;
//    }

//    if (objectName() != "moviesVLCPlayer")
//        qDebug() << "setting hwnd";
//    libvlc_media_player_set_hwnd(mediaPlayer_, hwnd);
//    mediaPlayerAttachedToSystemWindow_ = true;
//    updateMouseHook();
//    return true;
//}

//void VLCPlayer::updateMouseHook()
//{
//    if (!mediaPlayer_ || !shown_) // if not shown, don't capture hook back!
//        return;
//    //qDebug() << "updateMouseHook(): VLCPlayer" << this;
//    HWND hwnd = (HWND)libvlc_media_player_get_hwnd(mediaPlayer_);
//    if (hwnd)
//        VLCMouseHook::sharedInstance()->updateMouseHook(hwnd);
//}

//void VLCPlayer::onMouseMove()
//{
//    qDebug() << "-------------- ON MOUSE MOVE ---------------";
//    if (!fullscreen_)
//        return;
//    qDebug() << "\tplayer is fullscreen";

//    lastMouseActivityMoment_ = QDateTime::currentDateTimeUtc();
//    if (!panelShown_)
//    {
//        qDebug() << "\tpanel wasn't shown";
//        showPanel();
//    }
//    else
//        qDebug() << "\tpanel was already shown";
//}

//void VLCPlayer::checkMouseActivity()
//{
//    if (panelContainsMouse())
//        return;

//    QPoint currentMousePosition = QCursor::pos();
//    if (currentMousePosition != lastKnownMousePosition_)
//    {
//        lastMouseActivityMoment_ = QDateTime::currentDateTimeUtc();
//        lastKnownMousePosition_ = currentMousePosition;
//        showPanel(true);
//    }
//    else
//    {
//        lastKnownMousePosition_ = currentMousePosition;
//        int mouseIdlingInterval =
//                lastMouseActivityMoment_.msecsTo(
//                    QDateTime::currentDateTimeUtc());

//        if (mouseIdlingInterval > mouseActivityIntervalMsecs)
//        {
//            if (!panelContainsMouse())
//            {
//                hidePanel(true);
//            }
//        }
//    }
//}

//void VLCPlayer::updatePanelWidth()
//{
//    Q_ASSERT_X(window_, "updatePanelWidth()", "Window is not initialized");
//    Q_ASSERT_X(panelWindow_, "updatePanelWindow()", "Panel is not initialized");
//    if (!window_ || !panelWindow_)
//        return;
//    panelWindow_->setWidth(window_->width());
//}

//void VLCPlayer::setShown(bool shown)
//{
//    if (shown_ == shown)
//        return;
//    shown_ = shown;
//    emit shownChanged();
//}

//void VLCPlayer::showPanel(bool animated)
//{
//    Q_ASSERT_X(window_, "showPanel()", "Window is not initialized");
//    Q_ASSERT_X(panelWindow_, "showPanel()", "Panel window is not initialized");
//    if (!window_ || !panelWindow_)
//        return;

//    if (panelShown_)
//        return;

//    //	panelWindow_->showNormal();
//    //	panelWindow_->requestActivate();
//    //	panelWindow_->raise();

//    if (animated)
//    {
//        QPropertyAnimation *animation
//                = new QPropertyAnimation(panelWindow_, "y");
//        animation->setDuration(500);
//        animation->setStartValue(window_->height());
//        animation->setEndValue(window_->height() - panelWindow_->height());
//        animation->setEasingCurve(QEasingCurve::InOutQuart);

//        // Note: stopping the animation via it's stop()
//        // member function may (and probably will) lead
//        // to a memory leak because the finished() signal
//        // is not emitted if animation hasn't reached it's end.
//        // Happily, there is no need to stop the animation.
//        QObject::connect(animation, SIGNAL(finished()),
//                         animation, SLOT(deleteLater()));

//        animation->start();
//    }
//    else
//    {
//        panelWindow_->setY(window_->height() - panelWindow_->height());
//    }

//    panelShown_ = true;
//}

//void VLCPlayer::hidePanel(bool animated)
//{
//    Q_ASSERT_X(window_, "hidePanel()", "Window is not initialized");
//    Q_ASSERT_X(panelWindow_, "hidePanel()", "Panel window is not initialized");
//    if (!window_ || !panelWindow_)
//        return;

//    if (!panelShown_)
//        return;

//    qDebug() << "hide panel";

//    if (animated)
//    {
//        QPropertyAnimation *animation
//                = new QPropertyAnimation(panelWindow_, "y");
//        animation->setDuration(500);
//        animation->setStartValue(window_->height() - panelWindow_->height());
//        animation->setEndValue(window_->height());
//        animation->setEasingCurve(QEasingCurve::InOutQuart);

//        // Note: stopping the animation via it's stop()
//        // member function may (and probably will) lead
//        // to a memory leak because the finished() signal
//        // is not emitted if animation has'n reach it's end.
//        QObject::connect(animation, SIGNAL(finished()),
//                         animation, SLOT(deleteLater()));

//        animation->start();
//    }
//    else
//    {
//        panelWindow_->setY(window_->height());
//    }

//    panelShown_ = false;
//}

//void VLCPlayer::performPlay()
//{
//    shouldPauseOnPlayActuating_ = false;

//    if (!mediaPlayerAttachedToSystemWindow_)
//    {
//        // Try again later
//        QTimer::singleShot(100, this, SLOT(performPlay()));
//        return;
//    }

//    libvlc_media_player_set_media(mediaPlayer_, media_);

//    if (-1 == libvlc_media_player_play(mediaPlayer_))
//        reportError();
//}

//void VLCPlayer::onPlayingChanged()
//{
//    if (playing())
//    {
//        if (shouldPauseOnPlayActuating_)
//            pause();
//    }
//    else
//    {
//        shouldPauseOnPlayActuating_ = false;
//    }
//}

//void VLCPlayer::updateElapsedTimeUTC()
//{
//    elapsedTimeUTC_+=1000;
//    emit elapsedTimeUTCChanged();
//}

void VLCPlayer::subscribeToAcestreamEvents()
{
    int result = 0;

    if (!eventManager_acestream_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null event manager";
        return;
    }


    if (!subscribedToEvents_Acestream_.empty())
        return;

    const size_t eventCount = sizeof(acestreamEventTypesToSubscribe)/sizeof(acestreamEventTypesToSubscribe[0]);
    subscribedToEvents_Acestream_.reserve(eventCount);

    for (size_t i = 0; i < eventCount; ++i)
    {
        result = libvlc_event_attach(eventManager_acestream_, acestreamEventTypesToSubscribe[i], onVLCAcestreamEvent, this);

        if (result != 0)
        {
            qWarning("Can't attach to event: '%s'", libvlc_event_type_name(acestreamEventTypesToSubscribe[i]));
            //reportError();
        }
        else
        {
            subscribedToEvents_Acestream_.push_back(i);
#if LOGGING
            qDebug("Attached to event: '%s'", libvlc_event_type_name(acestreamEventTypesToSubscribe[i]));
#endif
        }
    }

    if (!mediaPlayer_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null media player";
        return;
    }
#if 0
    libvlc_audio_set_volume_callback(mediaPlayer_, &VLCPlayer::onVLCVolumeChanged);
#endif
}

void VLCPlayer::subscribeToMediaListEvents()
{
    int result = 0;

    if (!eventManager_MediaList_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null event manager";
        return;
    }


    if (!subscribedToEvents_MediaList_.empty())
        return;

    const size_t eventCount = sizeof(mediaListEventTypesToSubscribe)/sizeof(mediaListEventTypesToSubscribe[0]);
    subscribedToEvents_MediaList_.reserve(eventCount);

    for (size_t i = 0; i < eventCount; ++i)
    {
        result = libvlc_event_attach(eventManager_MediaList_, mediaListEventTypesToSubscribe[i], onVLCEvent, this);

        if (result != 0)
        {
            qWarning("Can't attach to event: '%s'", libvlc_event_type_name(mediaListEventTypesToSubscribe[i]));
            //reportError();
        }
        else
        {
            subscribedToEvents_MediaList_.push_back(i);
#if LOGGING
            qDebug("Attached to event: '%s'", libvlc_event_type_name(mediaListEventTypesToSubscribe[i]));
#endif
        }
    }

    if (!mediaPlayer_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null media player";
        return;
    }
#if 0
    libvlc_audio_set_volume_callback(mediaPlayer_, &VLCPlayer::onVLCVolumeChanged);
#endif
}

void VLCPlayer::subscribeToEvents()
{
    int result = 0;

    if (!eventManager_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null event manager";
        return;
    }


    if (!subscribedToEvents_.empty())
        return;

    const size_t eventCount = sizeof(eventTypesToSubscribe)/sizeof(eventTypesToSubscribe[0]);
    subscribedToEvents_.reserve(eventCount);

    for (size_t i = 0; i < eventCount; ++i)
    {
        result = libvlc_event_attach(eventManager_, eventTypesToSubscribe[i], onVLCEvent, this);

        if (result != 0)
        {
            qWarning("Can't attach to event: '%s'", libvlc_event_type_name(eventTypesToSubscribe[i]));
            //reportError();
        }
        else
        {
            subscribedToEvents_.push_back(i);
#if LOGGING
            qDebug("Attached to event: '%s'", libvlc_event_type_name(eventTypesToSubscribe[i]));
#endif
        }
    }

    if (!mediaPlayer_)
    {
        qDebug() << "Warning: Cannot subscribe to events with null media player";
        return;
    }
#if 0
    libvlc_audio_set_volume_callback(mediaPlayer_, &VLCPlayer::onVLCVolumeChanged);
#endif
}

//void VLCPlayer::unsubscribeFromEvents()
//{
//    for (QList<libvlc_event_type_t>::iterator i = subscribedToEvents_.begin();
//         i != subscribedToEvents_.end(); ++i)
//    {
//#if LOGGING
//        qDebug("Detaching event: '%s'", libvlc_event_type_name(*i));
//#endif
//        libvlc_event_detach(eventManager_, *i, onVLCEvent, this);
//    }
//    subscribedToEvents_.clear();

//    //unsubscribe from Media list events
//    for (QList<libvlc_event_type_t>::iterator i = subscribedToEvents_MediaList_.begin();
//         i != subscribedToEvents_MediaList_.end(); ++i)
//    {
//#if LOGGING
//        qDebug("Detaching event: '%s'", libvlc_event_type_name(*i));
//#endif
//        libvlc_event_detach(eventManager_MediaList_, *i, onVLCEvent, this);
//    }
//    subscribedToEvents_MediaList_.clear();


//    //unsubscribe from Acestream events
//    for (QList<libvlc_event_type_t>::iterator i = subscribedToEvents_Acestream_.begin();
//         i != subscribedToEvents_Acestream_.end(); ++i)
//    {
//#if LOGGING
//        qDebug("Detaching event: '%s'", libvlc_event_type_name(*i));
//#endif
//        libvlc_event_detach(eventManager_acestream_, *i, onVLCEvent, this);
//    }
//    subscribedToEvents_Acestream_.clear();
//}

//bool VLCPlayer::panelContainsMouse()
//{
//    Q_ASSERT_X(panelWindow_, "mouseIsActive()", "Panel window is not initialized");
//    if (!panelWindow_)
//        return false;

//    QPoint localCursorPosition =
//            window_->mapFromGlobal(QCursor::pos());
//    qDebug() << "LOCAL CURSOR POSITION:" << localCursorPosition;
//    qDebug() << "PANEL GEOMETRY:" << panelWindow_->geometry();
//    return panelWindow_->geometry().contains(localCursorPosition);
//}

void VLCPlayer::onVLCAcestreamEvent(const struct libvlc_event_t *event,
                                    void *userData)
{
    const char *error = "";
    const char *status = "";
    int state;

    VLCPlayer *vlcPlayer = (VLCPlayer *)userData;

    vlcPlayer->emit vlcEvent();

    if (event->type == libvlc_AcestreamError)
    {
        error = event->u.acestream_error.error;
        vlcPlayer->emit aceStreamError();
    }
    else if (event->type == libvlc_AcestreamStatus)
    {
        vlcPlayer->setStatus(event->u.acestream_status.status);
        //          status = event->u.acestream_status.status;
    }
    else if (event->type == libvlc_AcestreamState)
    {
        state = event->u.acestream_state.state;
    }else if(event->type == libvlc_AcestreamStatusRaw){
        status = event->u.acestream_status_raw.status;
        vlcPlayer->setStatusRaw(status);
//        vlcPlayer->emit statusChanged(QString(status));
    } else if(event->type == libvlc_AcestreamShowUserDataDialog){
        bool us = libvlc_acestream_object_user_data( vlcPlayer->getAcestream(), 1, 5 );
    }

#if LOGGING
    qDebug("onVLCAcestreamEvent-----------------------");
    //        qDebug("status - '%s'   error - '%s'   state  -  '%d'", status, error, state);
    qDebug("state  -  %d status - %s error - %s", state, status,error);
#endif
}


void VLCPlayer::onVLCEvent(const struct libvlc_event_t *event,
                           void *userData)
{
    // ----------------------------------------------------
    // WARNING: this callback is called on different thread
    // ----------------------------------------------------
    VLCPlayer *vlcPlayer = (VLCPlayer *)userData;

    vlcPlayer->emit vlcEvent();

    if (event->type == libvlc_MediaPlayerEndReached)
    {
        vlcPlayer->emit endReached();
        vlcPlayer->emit playingChanged(); // FIXME: Is this correct?
    }
    else if (event->type == libvlc_MediaPlayerLengthChanged)
    {
        vlcPlayer->emit mediaLengthChanged();
    }
    else if (event->type == libvlc_MediaPlayerTimeChanged)
    {
        vlcPlayer->emit timeChanged();
    }
    else if (event->type == libvlc_MediaPlayerPositionChanged)
    {
        vlcPlayer->emit positionChanged();
    }
    else if (event->type == libvlc_MediaPlayerPausableChanged)
    {
        vlcPlayer->emit pausableChanged();
    }
    else if (event->type == libvlc_MediaPlayerPlaying)
    {
        vlcPlayer->emit playingChanged();
    }
    else if (event->type == libvlc_MediaPlayerPaused)
    {
        vlcPlayer->emit playingChanged();
    }
    else if (event->type == libvlc_MediaPlayerStopped)
    {
        vlcPlayer->emit playingChanged();
        vlcPlayer->emit timeChanged();
        vlcPlayer->emit positionChanged();
    }
    else if (event->type == libvlc_MediaListItemAdded)
    {
        vlcPlayer->playMedia();
    }
    else if (event->type == libvlc_MediaListWillAddItem)
    {
#if LOGGING
        qDebug("libvlc_MediaListWillAddItem-----------------------");
#endif
    }
}

//#if 0
//void VLCPlayer::onVLCVolumeChanged(void *userData, float volume, bool mute)
//{
//    Q_UNUSED(volume);
//    Q_UNUSED(mute);
//#if LOGGING
//    qDebug("VLCPlayer::onVLCVolumeChanged(%p, %f, %d", userData, volume, (int)mute);
//#endif
//    VLCPlayer *vlcPlayer = static_cast<VLCPlayer *>(userData);
//    vlcPlayer->emit volumeChanged();
//    vlcPlayer->emit mutedChanged();
//}
//#endif

//HWND VLCPlayer::getHWNDForWindow(QWindow *window)
//{
//    if (window && window->handle())
//    {
//        QPlatformNativeInterface* iface = QGuiApplication::platformNativeInterface();
//        return static_cast<HWND>(
//                    iface->nativeResourceForWindow(QByteArrayLiteral("handle"), window));
//    }
//    return NULL;
//}

//QPointF VLCPlayer::localToWindow(qreal x, qreal y)
//{
//    qreal windowX = x;
//    qreal windowY = y;
//    QQuickItem *item = this;
//    while (item->parentItem())
//    {
//        windowX += item->x();
//        windowY += item->y();
//        item = item->parentItem();
//    }
//    return QPointF(windowX, windowY);
//}

void VLCPlayer::reportError()
{
    // FIXME:
    const char *errmsg = libvlc_errmsg();
    if (!errmsg)
        errmsg = "unknown error";
    std::cout << "Error: " << errmsg << std::endl;
    exit(-1);
}
