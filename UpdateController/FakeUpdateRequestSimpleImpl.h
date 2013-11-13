#ifndef FAKEUPDATEREQUESTSIMPLEIMPL_H
#define FAKEUPDATEREQUESTSIMPLEIMPL_H

#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"

class FakeUpdateRequestSimpleImpl : public UpdateRequest
{
    Q_OBJECT
public:
    explicit FakeUpdateRequestSimpleImpl(QObject *parent = 0);

    Q_INVOKABLE virtual void performRequest();
    
signals:
    
public slots:
    
};

#endif // FAKEUPDATEREQUESTSIMPLEIMPL_H
