#include "atmcontroller.h"

AtmController::AtmController(QObject* const parent)
    : QObject{parent}
    , m_bankCommDelegate{this}
    , m_cardReaderDelegate{this}
    , m_isAuthenticated{false}
    , m_cardInfo{nullptr}
{
    connect(&m_bankCommDelegate, &BankApiAccessManager::authenticationStarted,
            this, [this]() {
        emit authenticationStarted();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::authenticationSucceed,
            this, [this]() {
        m_isAuthenticated = true;
        emit authenticationSucceed();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::authenticationFailed,
            this, [this](QString error) {
        emit authenticationFailed(error);
    });

    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountListStarted,
            this, [this]() {
        emit fetchingAccountListStarted();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountListSucceed,
            this, [this](QList<BankAccount> accountList) {
        m_accountList = accountList;
        emit accountListChanged();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountListFailed,
            this, [this](QString error) {
        emit fetchingAccountListFailed(error);
    });

    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountBalanceStarted,
            this, [this]() {
        emit fetchingAccountBalanceStarted();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountBalanceSucceed,
            this, [this](qint64 accountBalance) {
        emit fetchingAccountBalanceSucceed(accountBalance);
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::fetchingAccountBalanceFailed,
            this, [this](QString error) {
        emit fetchingAccountBalanceFailed(error);
    });

    connect(&m_bankCommDelegate, &BankApiAccessManager::depositStarted,
            this, [this]() {
        emit depositStarted();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::depositSucceed,
            this, [this]() {
        emit depositSucceed();
    });
    connect(&m_bankCommDelegate, &BankApiAccessManager::depositFailed,
            this, [this](QString error) {
        emit depositFailed(error);
    });

    connect(&m_cardReaderDelegate, &CardReader::readingCardStarted,
            this, [this]() {
        emit readingCardStarted();
    });
    connect(&m_cardReaderDelegate, &CardReader::readingCardSucceed,
            this, &AtmController::readCard);
    connect(&m_cardReaderDelegate, &CardReader::readingCardSucceed,
            this, [this]() {
        emit readingCardSucceed();
    });
    connect(&m_cardReaderDelegate, &CardReader::readingCardFailed,
            this, [this](QString error) {
        emit readingCardFailed(error);
    });
}

int AtmController::initialize()
{
    int result = m_cardReaderDelegate.initialize();
    if (result != 0) {
        return -1;
    }

    return 0;
}

void AtmController::readCard(CardReader::CardInfo info)
{
    m_cardInfo = std::make_unique<CardReader::CardInfo>(info);
}

void AtmController::authenticate(qint32 pinNumber)
{
    if (m_cardInfo == nullptr) {
        return;
    }

    QMetaObject::invokeMethod(&m_bankCommDelegate, "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, *m_cardInfo),
                                Q_ARG(qint32, m_pinNumber));
}

void AtmController::fetchAccountList()
{
    if (m_cardInfo == nullptr || !m_isAuthenticated) {
        return;
    }

    QMetaObject::invokeMethod(&m_bankCommDelegate, "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, *m_cardInfo),
                                Q_ARG(qint32, m_pinNumber));
}

void AtmController::selectAccount(qint32 index)
{
    if (index >= m_accountList.size()) {
        return;
    }

    m_selectedAccountIndex = index;
    emit selectedAccountIndexChanged(index);
}

void AtmController::fetchAccountBalance()
{
    if (m_cardInfo == nullptr || !m_isAuthenticated) {
        return;
    }

    QMetaObject::invokeMethod(&m_bankCommDelegate, "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, *m_cardInfo),
                                Q_ARG(qint32, m_pinNumber),
                                Q_ARG(QString, m_accountList.at(m_selectedAccountIndex).name));
}

void AtmController::deposit(qint64 amount)
{
    if (m_cardInfo == nullptr || !m_isAuthenticated) {
        return;
    }

    QMetaObject::invokeMethod(&m_bankCommDelegate, "deposit", Qt::DirectConnection,
                                Q_ARG(CardReader::CardInfo, *m_cardInfo),
                                Q_ARG(qint32, m_pinNumber),
                                Q_ARG(QString, m_accountList.at(m_selectedAccountIndex).name),
                                Q_ARG(qint64, amount));
}

void AtmController::withdraw()
{
    m_cardInfo = nullptr;
    m_isAuthenticated = false;
    emit withdrawed();
}
