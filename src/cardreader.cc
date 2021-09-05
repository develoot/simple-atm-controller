#include <fcntl.h>
#include <unistd.h>

#include "cardreader.h"

CardReader::CardReader(QObject* parent, const QString& device)
    : QObject{parent}
    , m_device{device}
{
}

CardReader::~CardReader()
{
    close(m_fd);
}

int CardReader::initialize()
{
    m_fd = open(m_device.toStdString().c_str(), O_RDONLY | O_NONBLOCK, 0);
    if (m_fd == -1) {
        return -1;
    }

    // I prefer Qt's Object Tree & Ownership model over smart pointers.
    m_notify = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notify, &QSocketNotifier::activated, this, &CardReader::read);

    return 0;
}

void CardReader::read()
{
    CardInfo info = { .name = "John Doe" };
    emit readingCardSucceed(info);
}