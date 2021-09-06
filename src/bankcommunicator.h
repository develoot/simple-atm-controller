#ifndef _BANKCOMMUNICATOR_H
#define _BANKCOMMUNICATOR_H

#include <QtNetwork/QNetworkAccessManager>

#include "bankaccount.h"
#include "cardreader.h"

class BankCommunicator : public QObject {
    Q_OBJECT

public:
    BankCommunicator(QObject* const parent = nullptr,
                    const QString& baseUrl = QString{"https://api.mybank.com"});
    ~BankCommunicator() = default;

public slots:
    void authenticate(CardReader::CardInfo info, qint32 pinNumber);
    void fetchAccountList(CardReader::CardInfo info, qint32 pinNumber);
    void fetchAccountBalance(CardReader::CardInfo info, qint32 pinNumber, QString accountName);
    void deposit(CardReader::CardInfo info, qint32 pinNumber, QString accountName, qint64 amount);

signals:
    void authenticationStarted();
    void authenticationSucceed();
    void authenticationFailed(QString error);

    void fetchingAccountListStarted();
    void fetchingAccountListSucceed(QList<BankAccount> accoutList);
    void fetchingAccountListFailed(QString error);

    void fetchingAccountBalanceStarted();
    void fetchingAccountBalanceSucceed(qint64 accountBalance);
    void fetchingAccountBalanceFailed(QString error);

    void depositStarted();
    void depositSucceed();
    void depositFailed(QString error);

private:
    QNetworkReply* request(CardReader::CardInfo info, qint32 pinNumber, QString resourceUrl,
                            QJsonObject jsonObject);

    QString m_baseUrl;
    QNetworkAccessManager m_networkManager;
};

#endif
