#include <iostream>

#include <QTextStream>

int main(void)
{
    QTextStream(stdout) << "Hello, world!" << Qt::endl;
    return 0;
}
