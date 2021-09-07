#ifndef _BANK_API_ACCESS_MANAGER_INTERFACE_H
#define _BANK_API_ACCESS_MANAGER_INTERFACE_H

#include <QtCore>

#include "BankAccount.h"
#include "CardReader.h"

class BankApiAccessManagerBase : public QObject {
    Q_OBJECT

public:
    BankApiAccessManagerBase(QObject* const parent = nullptr)
        : QObject{parent} {};
    ~BankApiAccessManagerBase() = default;

public slots:
    virtual void authenticate(CardReader::CardInfo info, quint32 pinNumber) = 0;
    virtual void fetchAccountList(CardReader::CardInfo info, quint32 pinNumber) = 0;
    virtual void fetchAccountBalance(CardReader::CardInfo info,
                                        quint32 pinNumber, QString accountName) = 0;
    virtual void deposit(CardReader::CardInfo info, quint32 pinNumber,
                                        QString accountName, quint64 amount) = 0;

signals:
    void authenticationStarted();
    void authenticationSucceed();
    void authenticationFailed(QString error);

    void fetchingAccountListStarted();
    void fetchingAccountListSucceed(QList<BankAccount> accoutList);
    void fetchingAccountListFailed(QString error);

    void fetchingAccountBalanceStarted();
    void fetchingAccountBalanceSucceed(quint64 accountBalance);
    void fetchingAccountBalanceFailed(QString error);

    void depositStarted();
    void depositSucceed();
    void depositFailed(QString error);
};

#endif
