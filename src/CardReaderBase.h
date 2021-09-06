#ifndef _CARD_READER_INTERFACE_H
#define _CARD_READER_INTERFACE_H

#include <QtCore>

class CardReaderBase : public QObject {
    Q_OBJECT

public:
    CardReaderBase(QObject* const parent = nullptr)
        : QObject{parent} {};
    ~CardReaderBase() = default;

    struct CardInfo {
        QString name;
    };

    virtual int initialize() = 0;

public slots:
    virtual void read() = 0;

signals:
    void readingCardStarted();
    void readingCardSucceed(CardReaderBase::CardInfo info);
    void readingCardFailed(QString error);
};

#endif
