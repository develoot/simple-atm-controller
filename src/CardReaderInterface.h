#ifndef _CARD_READER_INTERFACE_H
#define _CARD_READER_INTERFACE_H

#include <QtCore>

class CardReaderInterface {
public:
    struct CardInfo {
        QString name;
    };

    virtual int initialize() = 0;

public slots:
    virtual void read() = 0;

signals:
    virtual void readingCardStarted() = 0;
    virtual void readingCardSucceed(CardReaderInterface::CardInfo info) = 0;
    virtual void readingCardFailed(QString error) = 0;
};

#endif
