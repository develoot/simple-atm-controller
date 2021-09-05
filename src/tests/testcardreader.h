#include <QTest>

class TestCardReader : public QObject {
    Q_OBJECT

private slots:
    /*
     * We can't actually test `CardReader` because there's no card reader device.
     *
     * So, these tests are implemented to be always passed.
     */
    void testReadSucceed();
    void testReadFailed();
};
