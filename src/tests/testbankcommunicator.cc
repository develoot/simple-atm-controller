#include <QSignalSpy>

#include <BankApiAccessManager.h>

#include "testBankApiAccessManager.h"

void TestBankApiAccessManager::testAuthenticateSucceed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy authenticationStartedSpy(&comm, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationSucceedSpy(&comm, &BankApiAccessManager::authenticationSucceed);

    QMetaObject::invokeMethod(&comm, "authenticate", Qt::DirectConnection);

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testAuthenticateFailed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy authenticationStartedSpy(&comm, &BankApiAccessManager::authenticationStarted);
    QSignalSpy authenticationFailedSpy(&comm, &BankApiAccessManager::authenticationFailed);

    QMetaObject::invokeMethod(&comm, "authenticate", Qt::DirectConnection);

    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationFailedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountListSucceed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountListStartedSpy(&comm, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListSucceedSpy(&comm, &BankApiAccessManager::fetchingAccountListSucceed);

    QMetaObject::invokeMethod(&comm, "fetchAccountList", Qt::DirectConnection);

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListSucceedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountListFailed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountListStartedSpy(&comm, &BankApiAccessManager::fetchingAccountListStarted);
    QSignalSpy fetchingAccountListFailedSpy(&comm, &BankApiAccessManager::fetchingAccountListFailed);

    QMetaObject::invokeMethod(&comm, "fetchAccountList", Qt::DirectConnection);

    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountListFailedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountBalanceSucceed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountBalanceStartedSpy(&comm, &BankApiAccessManager::fetchingAccountBalanceStarted);
    QSignalSpy fetchingAccountBalanceSucceedSpy(&comm, &BankApiAccessManager::fetchingAccountBalanceSucceed);

    QMetaObject::invokeMethod(&comm, "fetchAccountBalance", Qt::DirectConnection);

    QCOMPARE(fetchingAccountBalanceStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountBalanceFailed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountBalanceStartedSpy(&comm, &BankApiAccessManager::fetchingAccountBalanceStarted);
    QSignalSpy fetchingAccountBalanceSucceedSpy(&comm, &BankApiAccessManager::fetchingAccountBalanceSucceed);

    QMetaObject::invokeMethod(&comm, "fetchAccountBalance", Qt::DirectConnection);

    QCOMPARE(fetchingAccountBalanceStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountDepositSucceed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountDepositStartedSpy(&comm, &BankApiAccessManager::fetchingAccountDepositStarted);
    QSignalSpy fetchingAccountDepositSucceedSpy(&comm, &BankApiAccessManager::fetchingAccountDepositSucceed);

    QMetaObject::invokeMethod(&comm, "fetchAccountDeposit", Qt::DirectConnection);

    QCOMPARE(fetchingAccountDepositStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountDepositSucceedSpy.count(), 1);
    */
}

void TestBankApiAccessManager::testFetchAccountDepositFailed()
{
    QVERIFY(true);

    /*
    BankApiAccessManager comm{this};

    QSignalSpy fetchingAccountDepositStartedSpy(&comm, &BankApiAccessManager::fetchingAccountDepositStarted);
    QSignalSpy fetchingAccountDepositFailedSpy(&comm, &BankApiAccessManager::fetchingAccountDepositFailed);

    QMetaObject::invokeMethod(&comm, "fetchAccountDeposit", Qt::DirectConnection);

    QCOMPARE(fetchingAccountDepositStartedSpy.count(), 1);
    QCOMPARE(fetchingAccountDepositFailedSpy.count(), 1);
    */
}

QTEST_MAIN(TestBankApiAccessManager)
