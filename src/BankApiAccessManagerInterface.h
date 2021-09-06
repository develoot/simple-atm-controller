#ifndef _BANK_API_ACCESS_MANAGER_INTERFACE_H
#define _BANK_API_ACCESS_MANAGER_INTERFACE_H

#include "bankaccount.h"
#include "CardReader.h"

class BankApiAccessManagerInterface {
public slots:
    virtual void authenticate(CardReader::CardInfo info, qint32 pinNumber) = 0;
    virtual void fetchAccountList(CardReader::CardInfo info, qint32 pinNumber) = 0;
    virtual void fetchAccountBalance(CardReader::CardInfo info,
                                        qint32 pinNumber, QString accountName) = 0;
    virtual void deposit(CardReader::CardInfo info, qint32 pinNumber,
                                        QString accountName, qint64 amount) = 0;

signals:
    virtual void authenticationStarted() = 0;
    virtual void authenticationSucceed() = 0;
    virtual void authenticationFailed(QString error) = 0;

    virtual void fetchingAccountListStarted() = 0;
    virtual void fetchingAccountListSucceed(QList<BankAccount> accoutList) = 0;
    virtual void fetchingAccountListFailed(QString error) = 0;

    virtual void fetchingAccountBalanceStarted() = 0;
    virtual void fetchingAccountBalanceSucceed(qint64 accountBalance) = 0;
    virtual void fetchingAccountBalanceFailed(QString error) = 0;

    virtual void depositStarted() = 0;
    virtual void depositSucceed() = 0;
    virtual void depositFailed(QString error) = 0;
};

#endif
