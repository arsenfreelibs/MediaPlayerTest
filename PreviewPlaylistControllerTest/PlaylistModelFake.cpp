#include "PlaylistModelFake.h"

PlaylistModelFake::PlaylistModelFake(QObject *parent) :
    PlaylistModel(parent), _activeGenreFilter(false), _activeFavoriteFilter(false)
{
}

PlaylistModelFake::~PlaylistModelFake()
{
}

void PlaylistModelFake::setActiveGenreFilter(bool active)
{
    _activeGenreFilter = active;
}

bool PlaylistModelFake::getActiveGenreFilter()
{
    return _activeGenreFilter;
}

void PlaylistModelFake::setActiveFavoriteFilter(bool active)
{
    _activeFavoriteFilter = active;
}

bool PlaylistModelFake::getActiveFavoriteFilter()
{
    return _activeFavoriteFilter;
}
