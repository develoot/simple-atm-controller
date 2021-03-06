#include <QtTest>

#include <AtmController.h>
#include <BankApiAccessManagerBase.h>
#include <CardReaderBase.h>

class DummyCardReader : public CardReaderBase {
    Q_OBJECT

public:
    DummyCardReader(QObject* const parent = nullptr);
    ~DummyCardReader() = default;

    int initialize() override;

public slots:
    void read() override;
};

class DummyBankApiAccessManager : public BankApiAccessManagerBase {
    Q_OBJECT

public:
    DummyBankApiAccessManager(QObject* const parent = nullptr);
    ~DummyBankApiAccessManager() = default;

public slots:
    void authenticate(CardReaderBase::CardInfo info, quint32 pinNumber) override;
    void fetchAccountList(CardReaderBase::CardInfo info, quint32 pinNumber) override;
    void fetchAccountBalance(CardReaderBase::CardInfo info,
                            quint32 pinNumber, QString accountName) override;
    void deposit(CardReaderBase::CardInfo info, quint32 pinNumber,
                            QString accountName, quint64 amount) override;
};

class TestAtmController : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void testFetchAccountBalance();
    void testDeposit();

private:
    AtmController* m_controller = nullptr;
};

