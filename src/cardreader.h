#ifndef _CARDREADER_H
#define _CARDREADER_H

#include <QObject>
#include <QSocketNotifier>

#include "bankaccount.h"

class CardReader : public QObject {
    Q_OBJECT

public:
    CardReader(const QString& device = QString{"/dev/input/event77"}, QObject* parent = nullptr);
    ~CardReader();

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
    void readingCardSucceed(BankAccount account);
    void readingCardFailed();

private:
    QSocketNotifier* m_notify;
    QString m_device;
};

#endif
