#include <QCoreApplication>

#include "UpdateComplexTester.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UpdateComplexTester test;
    QTimer::singleShot(0, &test, SLOT(execute()));

    return a.exec();
}
