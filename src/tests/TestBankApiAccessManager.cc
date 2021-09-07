#include "TestBankApiAccessManager.h"

void TestBankApiAccessManager::initTestCase()
{
    m_manager = new BankApiAccessManager{this, "https://test.api.mybank.com"};
}

void TestBankApiAccessManager::testAuthenticateSuccess()
{
    QSignalSpy authenticationStartedSpy(m_manager, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationSucceedSpy(m_manager, &BankApiAccessManager::authenticationSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager, "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testAuthenticateFail()
{
    QSignalSpy authenticationStartedSpy(m_manager, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationFailedSpy(m_manager, &BankApiAccessManager::authenticationFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager, "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListSuccess()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListSucceedSpy(m_manager, &BankApiAccessManager::fetchingAccountListSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager, "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListFail()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(m_manager, &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager, "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceSuccess()
{
    QSignalSpy fetchingAccountBalanceStartedSpy(m_manager, &BankApiAccessManager::fetchingAccountBalanceStarted);
    QSignalSpy fetchingAccountBalanceSucceedSpy(m_manager, &BankApiAccessManager::fetchingAccountBalanceSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager, "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountBalanceStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceFail()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(m_manager, &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager, "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositSuccess()
{
    QSignalSpy depositStartedSpy(m_manager, &BankApiAccessManager::depositStarted);
    QSignalSpy depositSucceedSpy(m_manager, &BankApiAccessManager::depositSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager, "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositFail()
{
    QSignalSpy depositStartedSpy(m_manager, &BankApiAccessManager::depositStarted);
    QSignalSpy depositFailedSpy(m_manager, &BankApiAccessManager::depositFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager, "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositFailedSpy.count(), 1);
}

QTEST_MAIN(TestBankApiAccessManager)
