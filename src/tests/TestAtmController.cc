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

void DummyBankApiAccessManager::authenticate(CardReaderBase::CardInfo info, qint32 pinNumber)
{
    emit authenticationStarted();
    emit authenticationSucceed();
}

void DummyBankApiAccessManager::fetchAccountList(CardReaderBase::CardInfo info, qint32 pinNumber)
{
    emit fetchingAccountListStarted();

    QList<BankAccount> dummyList{};
    for (qint64 i = 0; i < 10; i++) {
        BankAccount account = { .name = QString{"Account %1"}.arg(i) };
        dummyList.append(account);
    }

    emit fetchingAccountListSucceed(dummyList);
}

void DummyBankApiAccessManager::fetchAccountBalance(CardReaderBase::CardInfo info, qint32 pinNumber,
                                                    QString accountName)
{
    emit fetchingAccountBalanceStarted();
    emit fetchingAccountBalanceSucceed(1337);
}

void DummyBankApiAccessManager::deposit(CardReaderBase::CardInfo info, qint32 pinNumber,
                                        QString accountName, qint64 amount)
{
    emit depositStarted();
    emit depositSucceed();
}

void TestAtmController::initTestCase()
{
    m_controller = std::make_unique<AtmController>(this, new DummyCardReader{},
                                                    new DummyBankApiAccessManager{});
}

void TestAtmController::init()
{
    QSignalSpy withdrawedSpy{m_controller.get(), &AtmController::withdrawed};
    QMetaObject::invokeMethod(m_controller.get(), "withdraw", Qt::DirectConnection);
    QCOMPARE(withdrawedSpy.count(), 1);

    m_controller->initialize();

    QSignalSpy authenticationStartedSpy{m_controller.get(), &AtmController::authenticationStarted};
    QSignalSpy authenticationSucceedSpy{m_controller.get(), &AtmController::authenticationSucceed};
    QMetaObject::invokeMethod(m_controller.get(), "authenticate", Qt::DirectConnection, Q_ARG(qint32, 77));
    QCOMPARE(authenticationStartedSpy.count(), 1);
    QCOMPARE(authenticationSucceedSpy.count(), 1);

    QSignalSpy fetchingAccountListStartedSpy{m_controller.get(), &AtmController::fetchingAccountListStarted};
    QSignalSpy accountListChangedSpy{m_controller.get(), &AtmController::accountListChanged};
    QMetaObject::invokeMethod(m_controller.get(), "fetchAccountList", Qt::DirectConnection);
    QCOMPARE(fetchingAccountListStartedSpy.count(), 1);
    QCOMPARE(accountListChangedSpy.count(), 1);

    QSignalSpy selectedAccountIndexChangedSpy{m_controller.get(), &AtmController::selectedAccountIndexChanged};
    QMetaObject::invokeMethod(m_controller.get(), "selectAccount", Qt::DirectConnection, Q_ARG(qint32, 2));
    QCOMPARE(selectedAccountIndexChangedSpy.count(), 1);
    QCOMPARE(m_controller->selectedAccountIndex(), 2);
}

void TestAtmController::testFetchAccountBalance()
{
    QSignalSpy fetchingAccountBalanceSucceedSpy{m_controller.get(), &AtmController::fetchingAccountBalanceSucceed};
    QMetaObject::invokeMethod(m_controller.get(), "fetchAccountBalance", Qt::DirectConnection);
    QCOMPARE(fetchingAccountBalanceSucceedSpy.count(), 1);
}

void TestAtmController::testDeposit()
{
    QSignalSpy depositSucceedSpy{m_controller.get(), &AtmController::depositSucceed};
    QMetaObject::invokeMethod(m_controller.get(), "deposit", Qt::DirectConnection, Q_ARG(qint64, 9900));
    QCOMPARE(depositSucceedSpy.count(), 1);
}

QTEST_MAIN(TestAtmController)

