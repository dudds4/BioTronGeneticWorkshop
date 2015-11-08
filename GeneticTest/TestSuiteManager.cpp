#include "TestSuiteManager.h"
#include <QTest>

TestSuiteManager::~TestSuiteManager()
{
    m_testSuites.clear();
}

void TestSuiteManager::addTestSuite(QObject* testSuite)
{
    m_testSuites.append(testSuite);
}

int TestSuiteManager::runAllTestSuites()
{
    int failed = 0;
    QObject* testSuite;
    int length = m_testSuites.size();

    for(int i = 0; i < length; i++)
    {
        testSuite = m_testSuites[i];
        failed += QTest::qExec(testSuite);

    }
    return failed;
}

int TestSuiteManager::runTestSuite(QObject* testSuite)
{
    int index = m_testSuites.indexOf(testSuite);
    if(index != -1)
    {
        return QTest::qExec(m_testSuites.at(index));
    }
    return 0;
}
