#include "TestBankApiAccessManager.h"

void TestBankApiAccessManager::initTestCase()
{
    m_manager = std::make_unique<BankApiAccessManager>(this, "https://test.api.mybank.com");
}

void TestBankApiAccessManager::testAuthenticateSuccess()
{
    QSignalSpy authenticationStartedSpy(m_manager.get(), &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationSucceedSpy(m_manager.get(), &BankApiAccessManager::authenticationSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager.get(), "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testAuthenticateFail()
{
    QSignalSpy authenticationStartedSpy(m_manager.get(), &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationFailedSpy(m_manager.get(), &BankApiAccessManager::authenticationFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager.get(), "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListSuccess()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListSucceedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager.get(), "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountListFail()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager.get(), "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceSuccess()
{
    QSignalSpy fetchingAccountBalanceStartedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountBalanceStarted);
    QSignalSpy fetchingAccountBalanceSucceedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountBalanceSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager.get(), "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountBalanceStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testFetchAccountBalanceFail()
{
    QSignalSpy fetchingAccountListStartedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(m_manager.get(), &BankApiAccessManager::fetchingAccountListFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager.get(), "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"));

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositSuccess()
{
    QSignalSpy depositStartedSpy(m_manager.get(), &BankApiAccessManager::depositStarted);
    QSignalSpy depositSucceedSpy(m_manager.get(), &BankApiAccessManager::depositSucceed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x0000;

    QMetaObject::invokeMethod(m_manager.get(), "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositSucceedSpy.count(), 1);
}

void TestBankApiAccessManager::testDepositFail()
{
    QSignalSpy depositStartedSpy(m_manager.get(), &BankApiAccessManager::depositStarted);
    QSignalSpy depositFailedSpy(m_manager.get(), &BankApiAccessManager::depositFailed);

    CardReader::CardInfo info = { .name = "dummy" };
    qint32 pinNumber = 0x6161;

    QMetaObject::invokeMethod(m_manager.get(), "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, info),
                                Q_ARG(qint32, pinNumber),
                                Q_ARG(QString, "Test"),
                                Q_ARG(qint64, 7777));

    QCOMPARE(depositStartedSpy.count(), 1);
    QCOMPARE(depositFailedSpy.count(), 1);
}

QTEST_MAIN(TestBankApiAccessManager)
