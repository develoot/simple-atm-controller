#ifndef _BANK_API_ACCESS_MANAGER_H
#define _BANK_API_ACCESS_MANAGER_H

#include <QtCore>
#include <QtNetwork>

#include "BankApiAccessManagerInterface.h"

class BankApiAccessManager : public QObject, public BankApiAccessManagerInterface {
    Q_OBJECT

public:
    BankApiAccessManager(QObject* const parent = nullptr,
                        const QString& baseUrl = QString{"https://api.mybank.com"});
    ~BankApiAccessManager() = default;

public slots:
    void authenticate(CardReader::CardInfo info, qint32 pinNumber) override;
    void fetchAccountList(CardReader::CardInfo info, qint32 pinNumber) override;
    void fetchAccountBalance(CardReader::CardInfo info, qint32 pinNumber, QString accountName) override;
    void deposit(CardReader::CardInfo info, qint32 pinNumber, QString accountName, qint64 amount) override;

signals:
    void authenticationStarted() override;
    void authenticationSucceed() override;
    void authenticationFailed(QString error) override;

    void fetchingAccountListStarted() override;
    void fetchingAccountListSucceed(QList<BankAccount> accoutList) override;
    void fetchingAccountListFailed(QString error) override;

    void fetchingAccountBalanceStarted() override;
    void fetchingAccountBalanceSucceed(qint64 accountBalance) override;
    void fetchingAccountBalanceFailed(QString error) override;

    void depositStarted() override;
    void depositSucceed() override;
    void depositFailed(QString error) override;

private:
    QNetworkReply* request(CardReader::CardInfo info, qint32 pinNumber, QString resourceUrl,
                            QJsonObject jsonObject);

    QString m_baseUrl;
    QNetworkAccessManager m_networkManager;
};

#endif
