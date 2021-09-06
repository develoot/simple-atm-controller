#ifndef _CARD_READER_H
#define _CARD_READER_H

#include <QtCore>

#include "CardReaderBase.h"

class CardReader : public CardReaderBase {
    Q_OBJECT

public:
    CardReader(QObject* parent = nullptr, QString device = "/dev/input/event77");
    ~CardReader();

    int initialize() override;

public slots:
    void read() override;

private:
    QSocketNotifier* m_notify;
    QString m_device;
    int m_fd;
};

#endif
