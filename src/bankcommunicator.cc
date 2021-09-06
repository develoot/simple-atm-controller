#include <QtCore>
#include <QtNetwork>

#include "bankcommunicator.h"

BankCommunicator::BankCommunicator(QObject* const parent, const QString& baseUrl)
    : QObject{parent}
    , m_baseUrl{baseUrl}
    , m_networkManager{this}
{
}

void BankCommunicator::authenticate(CardReader::CardInfo info, qint32 pinNumber)
{
    QJsonObject jsonObject;
    jsonObject.insert("name", QJsonValue::fromVariant(info.name));
    jsonObject.insert("pin", QJsonValue::fromVariant(pinNumber));
    QNetworkReply *const reply = request(info, pinNumber, "/auth", jsonObject);
    connect(reply, &QIODevice::readyRead, this, [this, reply] {
        QJsonParseError error;
        auto replyJson = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            emit authenticationFailed("Failed to parse a JSON response: " + error.errorString());
            return;
        }
        if (replyJson["status"].isUndefined()) {
            emit authenticationFailed("Expected item \"status\" is undefined in the response");
            return;
        }
        if (replyJson["status"] != "Succeed") {
            emit authenticationFailed("Invalid PIN");
            return;
        }
        emit authenticationSucceed();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply]() {
        emit authenticationFailed("Unknown error: " + reply->errorString());
    });
    connect(reply, &QNetworkReply::sslErrors, this, [this, reply]() {
        emit authenticationFailed("SSL error: " + reply->errorString());
    });
}

void BankCommunicator::fetchAccountList(CardReader::CardInfo info, qint32 pinNumber)
{
    QJsonObject jsonObject;
    jsonObject.insert("name", QJsonValue::fromVariant(info.name));
    jsonObject.insert("pin", QJsonValue::fromVariant(pinNumber));
    QNetworkReply *const reply = request(info, pinNumber, "/accounts", jsonObject);
    connect(reply, &QIODevice::readyRead, this, [this, reply] {
        QJsonParseError error;
        auto replyJson = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            emit fetchingAccountListFailed("Failed to parse a JSON response: " + error.errorString());
            return;
        }
        if (replyJson["status"].isUndefined()) {
            emit fetchingAccountListFailed("Expected item \"status\" is undefined in the response");
            return;
        }
        if (replyJson["status"] != "Succeed") {
            emit fetchingAccountListFailed("Invalid PIN");
            return;
        }
        if (replyJson["accountList"].isUndefined()) {
            emit fetchingAccountListFailed("Expected item \"accountList\" is undefined in the response");
        }
        QJsonArray accountListJson = replyJson["accountList"].toArray();
        QList<BankAccount> accountList;
        for (auto jsonValue : accountListJson) {
            accountList.push_back({jsonValue.toObject()["name"].toString()});
        }
        emit fetchingAccountListSucceed(accountList);
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply]() {
        emit fetchingAccountListFailed("Unknown error: " + reply->errorString());
    });
    connect(reply, &QNetworkReply::sslErrors, this, [this, reply]() {
        emit fetchingAccountListFailed("SSL error: " + reply->errorString());
    });
}

void BankCommunicator::fetchAccountBalance(CardReader::CardInfo info, qint32 pinNumber, QString accountName)
{
    QJsonObject jsonObject;
    jsonObject.insert("account", QJsonValue::fromVariant(accountName));
    jsonObject.insert("name", QJsonValue::fromVariant(info.name));
    jsonObject.insert("pin", QJsonValue::fromVariant(pinNumber));
    QNetworkReply *const reply = request(info, pinNumber, "/balance", jsonObject);
    connect(reply, &QIODevice::readyRead, this, [this, reply] {
        QJsonParseError error;
        auto replyJson = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            emit fetchingAccountBalanceFailed("Failed to parse a JSON response: " + error.errorString());
            return;
        }
        if (replyJson["status"].isUndefined()) {
            emit fetchingAccountBalanceFailed("Expected item \"status\" is undefined in the response");
            return;
        }
        if (replyJson["status"] != "Succeed") {
            emit fetchingAccountBalanceFailed("Invalid PIN");
            return;
        }
        if (replyJson["balance"].isUndefined()) {
            emit fetchingAccountListFailed("Expected item \"balance\" is undefined in the response");
            return;
        }
        emit fetchingAccountBalanceSucceed(replyJson["balance"].toInt());
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this]() {
        emit fetchingAccountBalanceFailed("Unknown error");
    });
    connect(reply, &QNetworkReply::sslErrors, this, [this]() {
        emit fetchingAccountBalanceFailed("Invalid SSL");
    });
}

void BankCommunicator::deposit(CardReader::CardInfo info, qint32 pinNumber, QString accountName,
                                qint64 amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("account", QJsonValue::fromVariant(accountName));
    jsonObject.insert("amount", QJsonValue::fromVariant(amount));
    jsonObject.insert("name", QJsonValue::fromVariant(info.name));
    jsonObject.insert("pin", QJsonValue::fromVariant(pinNumber));
    QNetworkReply *const reply = request(info, pinNumber, "/deposit", jsonObject);
    connect(reply, &QIODevice::readyRead, this, [this, reply] {
        QJsonParseError error;
        auto replyJson = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            emit depositFailed("Failed to parse a JSON response: " + error.errorString());
            return;
        }
        if (replyJson["status"].isUndefined()) {
            emit depositFailed("Expected item \"status\" is undefined in the response");
            return;
        }
        if (replyJson["status"] != "Succeed") {
            emit depositFailed("Invalid PIN");
            return;
        }
        emit depositSucceed();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this]() {
        emit depositFailed("Unknown error");
    });
    connect(reply, &QNetworkReply::sslErrors, this, [this]() {
        emit depositFailed("Invalid SSL");
    });
}

QNetworkReply* BankCommunicator::request(CardReader::CardInfo info, qint32 pinNumber, QString resourceUrl,
                                            QJsonObject jsonObject)
{
    QJsonDocument json{jsonObject};
    auto dataSize = QByteArray::number(json.toJson().size());

    QUrl serviceUrl{m_baseUrl + resourceUrl};
    QNetworkRequest request{serviceUrl};
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", dataSize);

    return m_networkManager.post(request, json.toJson());
}
