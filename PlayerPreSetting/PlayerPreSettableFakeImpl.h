#ifndef PLAYERPRESETTABLEFAKEIMPL_H
#define PLAYERPRESETTABLEFAKEIMPL_H

#include "../../../MediaPlayer/src/Controls/VLCPlayer/PlayerPreSettable.h"

class PlayerPreSettableFakeImpl : public PlayerPreSettable
{
private:
    bool _muted;
    float _volume;
public:
    PlayerPreSettableFakeImpl();

    virtual void setVolume(float volume);
    virtual void setMuted(bool muted);

    virtual float volume() const;
    virtual bool muted() const;
};

#endif // PLAYERPRESETTABLEFAKEIMPL_H
