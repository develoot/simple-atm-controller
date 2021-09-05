#include <fcntl.h>

#include "cardreader.h"

CardReader::CardReader(const QString& device, QObject *parent)
    : QObject{parent}
    , m_device{device}
{
}

int CardReader::initialize()
{
    int fd = open(m_device.toStdString().c_str(), O_RDONLY | O_NONBLOCK, 0);
    if (fd == -1) {
        return -1;
    }

    // I prefer Qt's Object Tree & Ownership model over smart pointers.
    m_notify = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(m_notify, &QSocketNotifier::activated, this, &CardReader::read);

    return 0;
}

void CardReader::read()
{
    CardInfo info = { .name = "John Doe" };
    emit readingCardSucceed(info);
}
