#include "TestAtmController.h"

DummyCardReader::DummyCardReader(QObject* const parent)
    : CardReaderBase{parent}
{
}

int DummyCardReader::initialize()
{
    DummyCardReader::CardInfo dummyCard  = {
        .name = "Dummy"
    };

    emit readingCardStarted();
    emit readingCardSucceed(dummyCard);

    return 0;
}

void DummyCardReader::read()
{
}

DummyBankApiAccessManager::DummyBankApiAccessManager(QObject* const parent)
    : BankApiAccessManagerBase{parent}
{
}

void DummyBankApiAccessManager::authenticate(CardReaderBase::CardInfo info, quint32 pinNumber)
{
    emit authenticationStarted();
    emit authenticationSucceed();
}

void DummyBankApiAccessManager::fetchAccountList(CardReaderBase::CardInfo info, quint32 pinNumber)
{
    emit fetchingAccountListStarted();

    QList<BankAccount> dummyList{};
    for (quint64 i = 0; i < 10; i++) {
        BankAccount account = { .name = QString{"Account %1"}.arg(i) };
        dummyList.append(account);
    }

    emit fetchingAccountListSucceed(dummyList);
}

void DummyBankApiAccessManager::fetchAccountBalance(CardReaderBase::CardInfo info, quint32 pinNumber,
                                                    QString accountName)
{
    emit fetchingAccountBalanceStarted();
    emit fetchingAccountBalanceSucceed(1337);
}

void DummyBankApiAccessManager::deposit(CardReaderBase::CardInfo info, quint32 pinNumber,
                                        QString accountName, quint64 amount)
{
    emit depositStarted();
    emit depositSucceed();
}

void TestAtmController::initTestCase()
{
    m_controller = new AtmController{this, new DummyCardReader{}, new DummyBankApiAccessManager{}};
}

void TestAtmController::init()
{
    QSignalSpy withdrawedSpy{m_controller, &AtmController::withdrawed};
    QMetaObject::invokeMethod(m_controller, "withdraw", Qt::DirectConnection);
    QCOMPARE(withdrawedSpy.count(), 1);

    m_controller->initialize();

    QSignalSpy authenticationStartedSpy{m_controller, &AtmController::authenticationStarted};
    QSignalSpy authenticationSucceedSpy{m_controller, &AtmController::authenticationSucceed};
    QMetaObject::invokeMethod(m_controller, "authenticate", Qt::DirectConnection, Q_ARG(quint32, 77));
    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);

    QSignalSpy fetchingAccountListStartedSpy{m_controller, &AtmController::fetchingAccountListStarted};
    QSignalSpy accountListChangedSpy{m_controller, &AtmController::accountListChanged};
    QMetaObject::invokeMethod(m_controller, "fetchAccountList", Qt::DirectConnection);
    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(accountListChangedSpy.count(), 1);

    QSignalSpy selectedAccountIndexChangedSpy{m_controller, &AtmController::selectedAccountIndexChanged};
    QMetaObject::invokeMethod(m_controller, "selectAccount", Qt::DirectConnection, Q_ARG(quint32, 2));
    QCOMPARE(selectedAccountIndexChangedSpy.count(), 1);
    QCOMPARE(m_controller->selectedAccountIndex(), 2);
}

void TestAtmController::testFetchAccountBalance()
{
    QSignalSpy fetchingAccountBalanceSucceedSpy{m_controller, &AtmController::fetchingAccountBalanceSucceed};
    QMetaObject::invokeMethod(m_controller, "fetchAccountBalance", Qt::DirectConnection);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
}

void TestAtmController::testDeposit()
{
    QSignalSpy depositSucceedSpy{m_controller, &AtmController::depositSucceed};
    QMetaObject::invokeMethod(m_controller, "deposit", Qt::DirectConnection, Q_ARG(quint64, 9900));
    QCOMPARE(depositSucceedSpy.count(), 1);
}

QTEST_MAIN(TestAtmController)

