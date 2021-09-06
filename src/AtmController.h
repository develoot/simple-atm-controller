#ifndef _ATM_CONTROLLER_H
#define _ATM_CONTROLLER_H

#include <memory>

#include <QtCore>

#include "BankAccount.h"
#include "BankApiAccessManager.h"
#include "CardReader.h"

class AtmController : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<BankAccount> accountList READ accountList NOTIFY accountListChanged);
    Q_PROPERTY(qint64 selectedAccountIndex READ selectedAccountIndex
                NOTIFY selectedAccountIndexChanged);

public:
    AtmController(QObject* const parent = nullptr,
                    CardReaderBase* cardReader = nullptr,
                    BankApiAccessManagerBase* bankApiAccessManager = nullptr);
    ~AtmController() = default;

    int initialize();

    QList<BankAccount> accountList() const { return m_accountList; };
    qint64 selectedAccountIndex() const { return m_selectedAccountIndex; };

public slots:
    void readCard(CardReader::CardInfo info);
    void authenticate(qint32 pinNumber);
    void fetchAccountList();
    void selectAccount(qint32 index);
    void fetchAccountBalance();
    void deposit(qint64 amount);
    void withdraw();

signals:
    void readingCardStarted();
    void readingCardSucceed();
    void readingCardFailed(QString error);

    void authenticationStarted();
    void authenticationSucceed();
    void authenticationFailed(QString error);

    void fetchingAccountListStarted();
    void fetchingAccountListSucceed();
    void fetchingAccountListFailed(QString error);

    void fetchingAccountBalanceStarted();
    void fetchingAccountBalanceSucceed(qint64 accountBalance);
    void fetchingAccountBalanceFailed(QString error);

    void depositStarted();
    void depositSucceed();
    void depositFailed(QString error);

    void withdrawed();

    void accountListChanged();
    void selectedAccountIndexChanged(qint32 index);

private:
    std::unique_ptr<BankApiAccessManagerBase> m_bankApiAccessManagerDelegate = nullptr;
    std::unique_ptr<CardReaderBase> m_cardReaderDelegate = nullptr;

    bool m_isAuthenticated = false;
    qint32 m_pinNumber = -1;
    qint64 m_selectedAccountIndex = -1;

    QList<BankAccount> m_accountList{};
    std::unique_ptr<CardReader::CardInfo> m_cardInfo{nullptr};
};

#endif
