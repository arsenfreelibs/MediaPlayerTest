#include "FakeUpdateRequestSimpleImpl.h"

FakeUpdateRequestSimpleImpl::FakeUpdateRequestSimpleImpl(QObject *parent) :
    UpdateRequest(parent)
{
}

void FakeUpdateRequestSimpleImpl::performRequest()
{
    std::vector<Version> versions;

    emit requestFinished(versions);
}
