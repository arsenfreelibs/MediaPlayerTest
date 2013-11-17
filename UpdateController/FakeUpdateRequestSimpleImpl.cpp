#include "FakeUpdateRequestSimpleImpl.h"

FakeUpdateRequestSimpleImpl::FakeUpdateRequestSimpleImpl(QObject *parent) :
    UpdateRequest(parent)
{
}

void FakeUpdateRequestSimpleImpl::performRequest()
{

    emit requestFinished(versions_);
}

void FakeUpdateRequestSimpleImpl::addToVersions(const Version &version)
{
    versions_.push_back(version);
}
