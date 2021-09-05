#include <QObject>
#include <QSocketNotifier>

class CardReader : public QObject {
    Q_OBJECT

public:
    CardReader(const QString& device = QString{"/dev/input/event77"});
    ~CardReader();

public slots:
    void read();

signals:
    void readingCardStarted();
    void readingCardSucceed();
    void readingCardFailed();

private:
    QSocketNotifier* m_notify;
};
