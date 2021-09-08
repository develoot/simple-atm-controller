#include "AtmController.h"

AtmController::AtmController(QObject* const parent, CardReaderBase* cardReader,
                                BankApiAccessManagerBase* bankApiAccessManager)
    : QObject{parent}
    , m_cardReaderDelegate{cardReader}
    , m_bankApiAccessManagerDelegate{bankApiAccessManager}
{
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::authenticationStarted,
            this, &AtmController::authenticationStarted);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::authenticationSucceed,
            this, [this]() {
        m_isAuthenticated = true;
        emit authenticationSucceed();
    });
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::authenticationFailed,
            this, &AtmController::authenticationFailed);

    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountListStarted,
            this, &AtmController::fetchingAccountListStarted);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountListSucceed,
            this, [this](QList<BankAccount> accountList) {
        m_accountList = accountList;
        emit accountListChanged();
    });
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountListFailed,
            this, &AtmController::fetchingAccountListFailed);

    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountBalanceStarted,
            this, &AtmController::fetchingAccountBalanceStarted);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountBalanceSucceed,
            this, &AtmController::fetchingAccountBalanceSucceed);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::fetchingAccountBalanceFailed,
            this, &AtmController::fetchingAccountBalanceFailed);

    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::depositStarted,
            this, &AtmController::depositStarted);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::depositSucceed,
            this, &AtmController::depositSucceed);
    connect(m_bankApiAccessManagerDelegate.get(), &BankApiAccessManagerBase::depositFailed,
            this, &AtmController::depositFailed);

    connect(m_cardReaderDelegate.get(), &CardReaderBase::readingCardStarted,
            this, &AtmController::readingCardStarted);
    connect(m_cardReaderDelegate.get(), &CardReaderBase::readingCardSucceed,
            this, &AtmController::readCard);
    connect(m_cardReaderDelegate.get(), &CardReaderBase::readingCardSucceed,
            this, &AtmController::readingCardSucceed);
    connect(m_cardReaderDelegate.get(), &CardReaderBase::readingCardFailed,
            this, &AtmController::readingCardFailed);
}

int AtmController::initialize()
{
    int result = m_cardReaderDelegate->initialize();
    if (result != 0) {
        return -1;
    }

    return 0;
}

void AtmController::readCard(CardReaderBase::CardInfo info)
{
    m_cardInfo = std::make_unique<CardReaderBase::CardInfo>(info);
}

void AtmController::authenticate(quint32 pinNumber)
{
    if (m_cardInfo == nullptr) {
        return;
    }

    QMetaObject::invokeMethod(m_bankApiAccessManagerDelegate.get(), "authenticate", Qt::DirectConnection,
                                Q_ARG(CardReaderBase::CardInfo, *m_cardInfo),
                                Q_ARG(quint32, m_pinNumber));
}

void AtmController::fetchAccountList()
{
    if (m_cardInfo == nullptr || !m_isAuthenticated) {
        return;
    }

    QMetaObject::invokeMethod(m_bankApiAccessManagerDelegate.get(), "fetchAccountList", Qt::DirectConnection,
                                Q_ARG(CardReaderBase::CardInfo, *m_cardInfo),
                                Q_ARG(quint32, m_pinNumber));
}

void AtmController::selectAccount(quint32 index)
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

    QMetaObject::invokeMethod(m_bankApiAccessManagerDelegate.get(), "fetchAccountBalance", Qt::DirectConnection,
                                Q_ARG(CardReaderBase::CardInfo, *m_cardInfo),
                                Q_ARG(quint32, m_pinNumber),
                                Q_ARG(QString, m_accountList[m_selectedAccountIndex].name));
}

void AtmController::deposit(quint64 amount)
{
    if (m_cardInfo == nullptr || !m_isAuthenticated) {
        return;
    }

    QMetaObject::invokeMethod(m_bankApiAccessManagerDelegate.get(), "deposit", Qt::DirectConnection,
                                Q_ARG(CardReaderBase::CardInfo, *m_cardInfo),
                                Q_ARG(quint32, m_pinNumber),
                                Q_ARG(QString, m_accountList[m_selectedAccountIndex].name),
                                Q_ARG(quint64, amount));
}

void AtmController::withdraw()
{
    m_cardInfo = nullptr;
    m_isAuthenticated = false;
    emit withdrawed();
}
