#include "testhelloworld.h"

void TestHelloWorld::success_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<QString>("result");

    QTest::newRow("Test 1") << "Hello, world!" << "Hello, world!";
    QTest::newRow("Test 2") << "Hello, world!" << "Hello, world!";
    QTest::newRow("Test 3") << "Hello, world!" << "Hello, world!";
}

void TestHelloWorld::success()
{
    QFETCH(QString, data);
    QFETCH(QString, result);

    QCOMPARE(data, result);
}

QTEST_MAIN(TestHelloWorld)
