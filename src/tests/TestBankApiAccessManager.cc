#include <BankApiAccessManager.h>

#include "TestBankApiAccessManager.h"

void TestBankApiAccessManager::testAuthenticateSuccess()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy authenticationStartedSpy(&manager, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationSucceedSpy(&manager, &BankApiAccessManager::authenticationSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(&manager, "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testAuthenticateFail()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy authenticationStartedSpy(&manager, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationFailedSpy(&manager, &BankApiAccessManager::authenticationFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(&manager, "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListSuccess()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy fetchingAccountListStartedSpy(&manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListSucceedSpy(&manager, &BankApiAccessManager::fetchingAccountListSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(&manager, "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListFail()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy fetchingAccountListStartedSpy(&manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(&manager, &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(&manager, "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceSuccess()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy fetchingAccountBalanceStartedSpy(&manager, &BankApiAccessManager::fetchingAccountBalanceStarted);
    QSignalSpy fetchingAccountBalanceSucceedSpy(&manager, &BankApiAccessManager::fetchingAccountBalanceSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(&manager, "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountBalanceStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceFail()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy fetchingAccountListStartedSpy(&manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(&manager, &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(&manager, "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositSuccess()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy depositStartedSpy(&manager, &BankApiAccessManager::depositStarted);
    QSignalSpy depositSucceedSpy(&manager, &BankApiAccessManager::depositSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(&manager, "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositFail()
{
    BankApiAccessManager manager{this, "https://test.api.mybank.com"};

    QSignalSpy depositStartedSpy(&manager, &BankApiAccessManager::depositStarted);
    QSignalSpy depositFailedSpy(&manager, &BankApiAccessManager::depositFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(&manager, "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositFailedSpy.count(), 1);
}

QTEST_MAIN(TestBankApiAccessManager)
