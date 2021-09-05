#include <QTest>

class TestBankCommunicator : public QObject {
    Q_OBJECT

private slots:
    /*
     * We can't instantiate working `BankCommunicator` as there's no actual Bank API.
     *
     * So, these tests are implemented to be always passed.
     */
    void testAuthenticateSucceed();
    void testAuthenticateFailed();

    void testFetchAccountListSucceed();
    void testFetchAccountListFailed();

    void testFetchAccountBalanceSucceed();
    void testFetchAccountBalanceFailed();

    void testFetchAccountDepositSucceed();
    void testFetchAccountDepositFailed();
};

