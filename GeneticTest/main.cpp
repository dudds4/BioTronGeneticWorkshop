#include <QGuiApplication>
#include "TestSuiteManager.h"

int main(int argc, char *argv[])
{
    TestSuiteManager tsm;
    int failed = tsm.runAllTestSuites();
    return failed;
}
