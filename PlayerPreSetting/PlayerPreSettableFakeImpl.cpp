#include "PlayerPreSettableFakeImpl.h"

PlayerPreSettableFakeImpl::PlayerPreSettableFakeImpl():
    _muted(false), _volume(1)
{
}

void PlayerPreSettableFakeImpl::setVolume(float volume)
{
    _volume = volume;
}

void PlayerPreSettableFakeImpl::setMuted(bool muted)
{
    _muted = muted;
}

float PlayerPreSettableFakeImpl::volume() const
{
    return _volume;
}

bool PlayerPreSettableFakeImpl::muted() const
{
    return _muted;
}
