#include <QObject>
#include <QNetworkAccessManager>

class BankCommunicator : public QObject {
    Q_OBJECT

public:
    BankCommunicator(const QUrl& baseUrl = QUrl{"https://api.mybank.com"});
    ~BankCommunicator();

public slots:
    void authenticate(qint32 pinNumber);
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
