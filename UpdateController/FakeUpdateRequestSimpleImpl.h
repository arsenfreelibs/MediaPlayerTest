#ifndef FAKEUPDATEREQUESTSIMPLEIMPL_H
#define FAKEUPDATEREQUESTSIMPLEIMPL_H

#include "../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h"

class FakeUpdateRequestSimpleImpl : public UpdateRequest
{
    Q_OBJECT
public:
    explicit FakeUpdateRequestSimpleImpl(QObject *parent = 0);

    Q_INVOKABLE virtual void performRequest();

    void addToVersions(const UpdateRequest::Version &version);
    
signals:

public slots:

private:
    std::vector<UpdateRequest::Version> versions_;

};

#endif // FAKEUPDATEREQUESTSIMPLEIMPL_H
