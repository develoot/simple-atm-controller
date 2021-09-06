#include <QtTest>

class TestCardReader : public QObject {
    Q_OBJECT

private slots:
    void testInitialize();
    void testReadSucceed();
    void testReadFailed();
};

