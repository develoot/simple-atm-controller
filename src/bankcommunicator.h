#ifndef _BANKCOMMUNICATOR_H
#define _BANKCOMMUNICATOR_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

#include "cardreader.h"

class BankCommunicator : public QObject {
    Q_OBJECT

public:
    BankCommunicator(QObject *parent = nullptr, const QUrl& baseUrl = QUrl{"https://api.mybank.com"});
    ~BankCommunicator();

public slots:
    void authenticate(CardReader::CardInfo info, qint32 pinNumber);
    void fetchAccountList();
    void fetchAccountBalance();
    void fetchAccountDeposit();

signals:
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

private:
    QNetworkAccessManager m_networkManager;
    QUrl m_baseUrl;
};

#endif
