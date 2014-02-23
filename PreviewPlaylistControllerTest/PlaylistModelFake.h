#ifndef PLAYLISTMODELFAKE_H
#define PLAYLISTMODELFAKE_H
#include "../../../MediaPlayer/src/Data/PlaylistModel.h"

class PlaylistModelFake : public PlaylistModel
{
    Q_OBJECT

private:
    bool _activeGenreFilter;
    bool _activeFavoriteFilter;
    int _genreID;

public:
    explicit PlaylistModelFake(QObject *parent = 0);    
    virtual ~PlaylistModelFake();

    virtual void setGenreID(int genre_id);
    int getGenreID();
    virtual void setActiveGenreFilter(bool active);
    bool getActiveGenreFilter();
    virtual void setActiveFavoriteFilter(bool active);
    bool getActiveFavoriteFilter();

signals:
    
public slots:
    
};

#endif // PLAYLISTMODELFAKE_H
