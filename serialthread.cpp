#include "serialthread.h"

SerialThread::SerialThread()
{
    port = new QSerialPort();
}

SerialThread::~SerialThread()
{
    if(port->isOpen())
        port->close();
    delete port;
}

void SerialThread::init(QString portName)
{
    if(port->isOpen())
    {
        port->close();
        emit log("Port "+ port->portName() +" is now closed");
    }
    port->setPortName(portName);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setParity(QSerialPort::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    if(port->open(QIODevice::ReadWrite))
    {
       emit log("Port "+ portName +" is now open");
        running=true;
    }
    else
    {
        emit log("Could not open "+ portName);
    }
}
void SerialThread::run()
{

    QByteArray data;
    while(running)
    {
        if(port->isOpen())
        {
        port->waitForReadyRead();
        data.append(port->readAll());
        if(data.size() !=0 && data.contains('\n'))
        {
            QList<QByteArray> split = data.split('\n');
            if(split.size() !=0)
            {
                data.clear();
                for(int i=0;i<split.size()-1;++i)
                {
                    split[i].remove(split[i].size()-1,1);
                    emit dataAvailable("Serial: " + split[i]);
                }
            }
            data.append(split[split.size()-1]);
        }
        }
        else
        {
            emit log("Still running");
            QThread::sleep(1000);
        }
    }

}

void SerialThread::sendData(QString data)
{

    port->write(data.toLocal8Bit().data(),data.size());
}

void SerialThread::toggle()
{
 ledOn = !ledOn;
 QByteArray command;
 command.append('c');
 command.append(ledOn + '0');
 command.append('\n');
 port->write(command.data(),command.length());
}

void SerialThread::stop()
{
    running=false;
    emit log ("Stopped...");

}
