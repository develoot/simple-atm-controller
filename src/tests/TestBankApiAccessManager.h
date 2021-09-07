#include <QtTest>

#include <BankApiAccessManager.h>

class TestBankApiAccessManager : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();

    void testAuthenticateSuccess();
    void testAuthenticateFail();

    void testFetchAccountListSuccess();
    void testFetchAccountListFail();

    void testFetchAccountBalanceSuccess();
    void testFetchAccountBalanceFail();

    void testDepositSuccess();
    void testDepositFail();

private:
    BankApiAccessManager* m_manager = nullptr;
};

