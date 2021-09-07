#include <QtTest>

class TestCardReader : public QObject {
    Q_OBJECT

private slots:
    void testReadSucceed();
    void testReadFailed();
};

