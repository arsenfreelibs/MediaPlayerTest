#ifndef VLCPLAYER_H
#define VLCPLAYER_H

//#include <windef.h>

//#include <vlc/vlc.h>
#include <acestreamplayer/vlc.h>
#include <QObject>


//#include <QDateTime>
#include <QList>
//#include <QQuickItem>

class VLCPlayerWindow;

class VLCPlayer : public QObject
{
	Q_OBJECT
//	Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
//	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
//    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

//	Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
//	Q_PROPERTY(qint64 mediaLength READ mediaLength NOTIFY mediaLengthChanged)
//	Q_PROPERTY(qint64 time READ time WRITE setTime NOTIFY timeChanged)
//	Q_PROPERTY(float position READ position NOTIFY positionChanged)
//	Q_PROPERTY(bool pausable READ pausable NOTIFY pausableChanged)
//	Q_PROPERTY(QString aspectRatio
//			   READ aspectRatio
//			   WRITE setAspectRatio
//			   NOTIFY aspectRatioChanged)
//	Q_PROPERTY(bool widescreen READ widescreen WRITE setWidescreen NOTIFY widescreenChanged)
//	Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
//	Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
////	Q_PROPERTY(bool panelVisible READ panelVisible WRITE setPanelVisible NOTIFY panelVisibleChanged)
//	Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)
//	Q_PROPERTY(bool shown READ shown NOTIFY shownChanged)

//    Q_PROPERTY(bool isTVStream READ isTVStream WRITE setIsTVStream NOTIFY isTVStreamChanged)
//    Q_PROPERTY(int totalTimeUTC READ totalTimeUTC WRITE setTotalTimeUTC NOTIFY totalTimeUTCChanged)
//    Q_PROPERTY(int elapsedTimeUTC READ elapsedTimeUTC WRITE setElapsedTimeUTC NOTIFY elapsedTimeUTCChanged)

public:
    explicit VLCPlayer(QObject *parent = 0);
	virtual ~VLCPlayer();

//	void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);


//	// This function indicates whether the player window
//	// is shown or hidden.
//	bool shown() const { return shown_; }

//	QString source() const { return source_; }
//	QString title() const { return title_; }
//    QString status() const { return status_; }
//    QString statusRaw() const { return statusRaw_;}
    libvlc_acestream_object_t* getAcestream() const {return acestream;}



//	bool playing() const;

//	// Returns length of current media in milliseconds.
//	// Returns zero is there is no media.
//	qint64 mediaLength() const;

//	// Returns current playback position in milliseconds.
//	// Returns zero if there is no media.
//	qint64 time() const;

//	// Returns current playback position in range [0.0, 1.0]
//	// where 1.0 corresponds to the end of the video.
//	// Returns zero if there is no media.
//	float position() const;

//	// Returns whether the player can be paused during playback
//	// (this probably depends on the media type). The return value
//	// does not depend on whether the player is playing at the moment
//	bool pausable() const;

//	// Returns aspect ratio of the currently played video
//	// in format "16:9".
//	QString aspectRatio() const;
//	bool widescreen() const;

//	// Returns volume in range [0, 1].
//	float volume() const;
//	bool muted() const;
//    bool isTVStream() const;
//    int totalTimeUTC() const;
//    int elapsedTimeUTC() const;

////	bool panelVisible() const { return panelVisible_; }

//	bool fullscreen() const { return fullscreen_; }
	    
signals:
    void vlcEvent();
    void shownChanged();
    void sourceChanged();
	void titleChanged();
	void playingChanged();
	void endReached();
	void mediaLengthChanged();
	void timeChanged();
	void positionChanged();
	void pausableChanged();
	void aspectRatioChanged();
	void widescreenChanged();
	void volumeChanged();
	void mutedChanged();
    void isTVStreamChanged();
    void totalTimeUTCChanged();
    void elapsedTimeUTCChanged();
	void fullscreenChanged();
	void doubleClicked();
    void mediaListItemAdded();
    void statusChanged(QString status);

public slots:
//	// The show() function isn't intended to be used
//	// for showing player fullscreen. This function
//	// shall only be used for showing the player screen
//	// when it's hidden.
//	void show();

//	// This function hides the player screen. Next time
//	// the player is shown in regular (not fullscreen) mode
//	// no matter whether it was fullscreen or not at the moment
//	// when hide() was called.
//	void hide();

//    void playURL(const QString &url, const QString &title = tr("Untitled"));

    void playTorrentURL(const QString &url, const QString &title = tr("Untitled"));

//    void playAvailableURL(const QString &url, const QString &torrentUrl,const QString &title = tr("Untitled"));


//	//the file has to be in one of the following formats /perhaps a little bit outdated)
//	/*
//	[file:///]filename			   Plain media file
//	http://ip:port/file            HTTP URL
//	ftp://ip:port/file             FTP URL
//	mms://ip:port/file             MMS URL
//	screen://                      Screen capture
//	[dvd://][device][@raw_device]  DVD device
//	[vcd://][device]               VCD device
//	[cdda://][device]              Audio CD device
//	udp:[[<source address>]@[<bind address>][:<bind port>]]
//	*/
//	void setSource(const QString &source);
//	void setTitle(const QString &title);
    void setStatus(const QString &status);
    void setStatusRaw(const QString &status);
//    void play();
//    void playMedia();
//	void pause();
//	void stop();
//	void setTime(qint64 time);
//	void setPosition(float position);
//	void setAspectRatio(const QString &aspectRatio);
//	void setWidescreen(bool widescreen);
//	void setVolume(float volume);
//	void setMuted(bool muted);
//    void setIsTVStream(bool isTVstream);
//    void setTotalTimeUTC(int totalTimeUTC);
//    void setElapsedTimeUTC(int elapsedTimeUTC);
//	Q_INVOKABLE void toggleMute();

//	// Updates the fullscreen property of the player and enlarges
//	// the video area so that it fits the whole screen.
//	// If player isn't shown (namely, shown() returns false)
//	// then the function only updates the property and
//	// doesn't adjust the video area.
//	void setFullscreen(bool fullscreen);


protected slots:
//	// Just setter that emits shownChanged() signal.
//	void setShown(bool shown);

//	void doubleClickHookTriggered();

//	// Shows the embedded control panel.
//	// (The embedded control panel is intended
//	// for using in fullscreen mode).
//	// If panel is already shown then the function does nothing.
//	void showPanel(bool animated = false);

//	// Hides the embedded control panel.
//	// If panel is'n shown then the function does nothing.
//	void hidePanel(bool animated = false);

//	bool createNativeWindow();
//	bool attachHWND();
//	void updateMouseHook();

//	void onMouseMove();
//	void checkMouseActivity();

//	void updatePanelWidth();

//	void performPlay();

//	void onPlayingChanged();

//    void updateElapsedTimeUTC();

protected:
    void subscribeToEvents();
    void subscribeToMediaListEvents();
    void subscribeToAcestreamEvents();
//	void unsubscribeFromEvents();
//	bool panelContainsMouse();
//    void CreateNewLibVlcMediaDescriptor(const QString &source);

//	HWND getHWNDForWindow(QWindow *window);

//	// Translates given x and y
//	// to the window coordinate system.
//	QPointF localToWindow(qreal x, qreal y);

    void reportError();

	bool mediaPlayerAttachedToSystemWindow_;

	QString source_;
	QString title_;
    QString status_;
    QString statusRaw_;

	bool shown_;
	bool panelShown_;
    bool isTVStream_ = false;
    int totalTimeUTC_;
    int elapsedTimeUTC_;
//    QTimer *updateElapsedTimeUTCTimer_;

//	VLCPlayerWindow *window_;
//	VLCPlayerWindow *panelWindow_;

	bool fullscreen_;

	bool windowWasMaximized_;

//	QDateTime lastMouseActivityMoment_;
//	QPoint lastKnownMousePosition_;
//	QTimer *mouseTrackTimer_;

//	QTimer *hookUpdateTimer_;

	libvlc_instance_t *vlcInstance_;
	libvlc_media_player_t *mediaPlayer_;
	libvlc_media_t *media_;
	libvlc_event_manager_t *eventManager_;
    libvlc_event_manager_t *eventManager_MediaList_;
    libvlc_event_manager_t *eventManager_acestream_;

	QList<libvlc_event_type_t> subscribedToEvents_;
    QList<libvlc_event_type_t> subscribedToEvents_MediaList_;
    QList<libvlc_event_type_t> subscribedToEvents_Acestream_;

    libvlc_acestream_object_t *acestream;
    libvlc_media_list_player_t *media_list_player;
    libvlc_media_list_t *media_list;

	bool shouldPauseOnPlayActuating_;

    static void onVLCEvent(const struct libvlc_event_t *event,
                           void *userData);

    static void onVLCAcestreamEvent(const struct libvlc_event_t *event, void *userData);

//#if 0
//	static void onVLCVolumeChanged(void *userData, float volume, bool mute);
//#endif
	static libvlc_event_type_t eventTypesToSubscribe[];

    static libvlc_event_type_t mediaListEventTypesToSubscribe[];

    static libvlc_event_type_t acestreamEventTypesToSubscribe[];

	static const int mouseActivityIntervalMsecs;
};

Q_DECLARE_METATYPE(VLCPlayer *)

#endif // VLCPLAYER_H
