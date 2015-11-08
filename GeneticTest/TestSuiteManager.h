#ifndef TESTSUITEMANAGER_H
#define TESTSUITEMANAGER_H

#include <QObject>
#include <QVector>

class TestSuiteManager : public QObject
{
    Q_OBJECT
public:
    TestSuiteManager(){};
    ~TestSuiteManager();

    void addTestSuite(QObject* testSuite);

    int runAllTestSuites();

    int runTestSuite(QObject* testSuite);

private:
    QVector<QObject*> m_testSuites;

};

#endif // TESTSUITEMANAGER_H
