#ifndef _ATMCONTROLLER_H
#define _ATMCONTROLLER_H

#include <QObject>
#include <QVector>

#include "cardreader.h"
#include "bankaccount.h"
#include "bankcommunicator.h"

class AtmController : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVector<BankAccount> accountList READ accountList NOTIFY accountListChanged);
    Q_PROPERTY(BankAccount selectedAccount READ selectedAccount NOTIFY selectedAccountChanged);

public:
    AtmController() = default;
    ~AtmController() = default;

    QVector<BankAccount> accountList() const { return m_accountList; };
    BankAccount selectedAccount() const { return m_selectedAccount; };

public slots:
    void readCard();
    void authenticate(qint32 pinNumber);
    void fetchAccountList();
    void selectAccount(qint32 index);
    void fetchAccountBalance();
    void fetchAccountDeposit();
    void withdrawOperation();

signals:
    void readingCardStarted();
    void readingCardSucceed();
    void readingCardFailed();

    void authenticationStarted();
    void authenticationSucceed();
    void authenticationFailed();

    void fetchingAccountListStarted();
    void fetchingAccountListSucceed();
    void fetchingAccountListFailed();

    void fetchingAccountBalanceStarted();
    void fetchingAccountBalanceSucceed();
    void fetchingAccountBalanceFailed();

    void fetchingAccountDepositStarted();
    void fetchingAccountDepositSucceed();
    void fetchingAccountDepositFailed();

    void withdrawed();

    void accountListChanged();
    void selectedAccountChanged();

private:
    BankCommunicator bankCommDelegate;
    CardReader cardReaderDelegate;

    bool m_isAuthenticated = false;
    QVector<BankAccount> m_accountList;
    BankAccount m_selectedAccount;
};

#endif
