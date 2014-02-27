#include "PreviewPlaylistControllerSettableFake.h"

PreviewPlaylistControllerSettableFake::PreviewPlaylistControllerSettableFake():
    _index(0)
{
}

void PreviewPlaylistControllerSettableFake::setFiltersByTvCategoryModelIntex(int index)
{
    _index = index;
}

int PreviewPlaylistControllerSettableFake::getTvCategoryModelIntex()
{
    return _index;
}
