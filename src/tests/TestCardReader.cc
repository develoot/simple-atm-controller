#include <CardReader.h>

#include "TestCardReader.h"

void TestCardReader::testInitialize()
{
    CardReader reader{this};
    QCOMPARE(reader.initialize(), 0);
}

void TestCardReader::testReadSucceed()
{
    CardReader reader{this, "/path/to/test/dev"};
    QCOMPARE(reader.initialize(), 0);

    QSignalSpy readingCardStartedSpy(&reader, &CardReader::readingCardStarted);
    QSignalSpy readingCardSucceedSpy(&reader, &CardReader::readingCardSucceed);

    QMetaObject::invokeMethod(&reader, "read", Qt::DirectConnection);

    QCOMPARE(readingCardStartedSpy.count(), 1);
    QCOMPARE(readingCardSucceedSpy.count(), 1);
}

void TestCardReader::testReadFailed()
{
    CardReader reader{this, "/path/to/invalid/dev"};
    QCOMPARE(reader.initialize(), 0);

    QSignalSpy readingCardStartedSpy(&reader, &CardReader::readingCardStarted);
    QSignalSpy readingCardFailedSpy(&reader, &CardReader::readingCardFailed);

    QMetaObject::invokeMethod(&reader, "read", Qt::DirectConnection);

    QCOMPARE(readingCardStartedSpy.count(), 1);
    QCOMPARE(readingCardFailedSpy.count(), 1);
}

QTEST_MAIN(TestCardReader)
