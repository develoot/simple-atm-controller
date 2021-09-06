#include <fcntl.h>
#include <unistd.h>

#include "CardReader.h"

CardReader::CardReader(QObject* parent, QString device)
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

    m_notify = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notify, &QSocketNotifier::activated, this, &CardReader::read);

    return 0;
}

void CardReader::read()
{
    CardInfo info = { .name = "John Doe" };
    emit readingCardSucceed(info);
}
