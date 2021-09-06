#ifndef _CARD_READER_H
#define _CARD_READER_H

#include <QtCore>

#include "CardReaderInterface.h"

class CardReader : public QObject, public CardReaderInterface {
    Q_OBJECT

public:
    CardReader(QObject* parent = nullptr, QString device = "/dev/input/event77");
    ~CardReader();

    int initialize() override;

public slots:
    void read() override;

signals:
    void readingCardStarted() override;
    void readingCardSucceed(CardReader::CardInfo info) override;
    void readingCardFailed(QString error) override;

private:
    QSocketNotifier* m_notify;
    QString m_device;
    int m_fd;
};

#endif
