#ifndef PREVIEWPLAYLISTCONTROLLERSETTABLEFAKE_H
#define PREVIEWPLAYLISTCONTROLLERSETTABLEFAKE_H

#include "QObject"
#include "../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistControllerSettable.h"

class PreviewPlaylistControllerSettableFake : public PreviewPlaylistControllerSettable
{
    Q_INTERFACES( PreviewPlaylistControllerSettable )

private:
    int _index;

public:
    PreviewPlaylistControllerSettableFake();

    virtual void setFiltersByTvCategoryModelIntex(int index);
    virtual int getTvCategoryModelIntex();
    virtual void setHD_Filter(bool active);
    bool virtual hdFilter() const;
    virtual void setSD_Filter(bool active);
    bool virtual sdFilter() const;

};

#endif // PREVIEWPLAYLISTCONTROLLERSETTABLEFAKE_H
