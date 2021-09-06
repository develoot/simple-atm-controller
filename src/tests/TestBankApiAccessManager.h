#include <QtTest>

class TestBankApiAccessManager : public QObject {
    Q_OBJECT

private slots:
    void testAuthenticateSuccess();
    void testAuthenticateFail();

    void testFetchAccountListSuccess();
    void testFetchAccountListFail();

    void testFetchAccountBalanceSuccess();
    void testFetchAccountBalanceFail();

    void testDepositSuccess();
    void testDepositFail();
};

