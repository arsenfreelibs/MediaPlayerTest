#include <QCoreApplication>
#include <QTimer>
#include "../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h"
#include "../../../MediaPlayer/src/Data/UserProfile.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h"
#include "../../../MediaPlayer/src/Protocol/NetworkRequestManager.h"
#include "NetworkFilmProtocolTester.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    NetworkFilmProtocolTester netTest;
    QTimer::singleShot(0, &netTest, SLOT(execute()));

    return a.exec();
}
