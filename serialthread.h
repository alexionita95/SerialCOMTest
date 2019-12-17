#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>
#include <QSharedPointer>

class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread();
    ~SerialThread() override;
    void init(QString portName);
    void stop();
    void run() override;
    void sendData(QString data);
    void toggle();
signals:
void dataAvailable(QString data);
void log(QString data);

public slots:

private:
bool ledOn;
QSerialPort* port;
bool running;

};

#endif // SERIALTHREAD_H
