#ifndef _CARDREADER_H
#define _CARDREADER_H

#include <QObject>
#include <QSocketNotifier>

class CardReader : public QObject {
    Q_OBJECT

public:
    CardReader(QObject* parent = nullptr, const QString& device = QString{"/dev/input/event77"});
    ~CardReader();

    struct CardInfo {
        QString name;
    };

    int initialize();

public slots:
    /**
     * Read a card from a card reader device.
     *
     * This slot is implemented to be always succeed as there's no actual card device.
     */
    void read();

signals:
    void readingCardStarted();
    void readingCardSucceed(CardInfo info);
    void readingCardFailed(QString error);

private:
    QSocketNotifier* m_notify;
    QString m_device;
    int m_fd;
};

#endif
