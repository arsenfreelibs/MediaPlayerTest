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

void PreviewPlaylistControllerSettableFake::setHD_Filter(bool active)
{
}

bool PreviewPlaylistControllerSettableFake::hdFilter() const
{
}

void PreviewPlaylistControllerSettableFake::setSD_Filter(bool active)
{
}

bool PreviewPlaylistControllerSettableFake::sdFilter() const
{
}
