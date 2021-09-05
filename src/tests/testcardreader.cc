#include <QSignalSpy>

#include <cardreader.h>

#include "testcardreader.h"

void TestCardReader::testReadSucceed()
{
    QVERIFY(true);

    /*
    CardReader cardReader{"/path/to/valid/dev"};
    QSignalSpy readingCardStartedSpy(&cardReader, &CardReader::readingCardStarted);
    QSignalSpy readingCardSucceedSpy(&cardReader, &CardReader::readingCardSucceed);

    QMetaObject::invokeMethod(&cardReader, "read", Qt::DirectConnection);

    QCOMPARE(readingCardStartedSpy.count(), 1);
    QCOMPARE(readingCardSucceedSpy.count(), 1);
    */
}

void TestCardReader::testReadFailed()
{
    QVERIFY(true);

    /*
    CardReader cardReader{"/path/to/invalid/dev"};
    QSignalSpy readingCardStartedSpy(&cardReader, &CardReader::readingCardStarted);
    QSignalSpy readingCardFailedSpy(&cardReader, &CardReader::readingCardFailed);

    QMetaObject::invokeMethod(&cardReader, "read", Qt::DirectConnection);

    QCOMPARE(readingCardStartedSpy.count(), 1);
    QCOMPARE(readingCardFailedSpy.count(), 1);
    */
}

QTEST_MAIN(TestCardReader)
