#ifndef _BANK_API_ACCESS_MANAGER_H
#define _BANK_API_ACCESS_MANAGER_H

#include <QtCore>
#include <QtNetwork>

#include "BankApiAccessManagerBase.h"

class BankApiAccessManager : public BankApiAccessManagerBase {
    Q_OBJECT

public:
    BankApiAccessManager(QObject* const parent = nullptr,
                        const QString& baseUrl = QString{"https://api.mybank.com"});
    ~BankApiAccessManager() = default;

public slots:
    void authenticate(CardReader::CardInfo info, quint32 pinNumber) override;
    void fetchAccountList(CardReader::CardInfo info, quint32 pinNumber) override;
    void fetchAccountBalance(CardReader::CardInfo info, quint32 pinNumber, QString accountName) override;
    void deposit(CardReader::CardInfo info, quint32 pinNumber, QString accountName, quint64 amount) override;

private:
    QNetworkReply* request(CardReader::CardInfo info, quint32 pinNumber, QString resourceUrl,
                            QJsonObject jsonObject);

    QString m_baseUrl;
    QNetworkAccessManager m_networkManager;
};

#endif
