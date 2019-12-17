#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port=new QSerialPort;
    connect(port,&QSerialPort::readyRead,this, &MainWindow::onSerialReadyRead);
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
        ui->comboBox->addItem(serialPortInfo.portName());
        }

    thread=new SerialThread();
    connect(thread,&SerialThread::log,this,&MainWindow::onLog);
    connect(thread,&SerialThread::dataAvailable,this,&MainWindow::onSerialDataAvailable);
}

MainWindow::~MainWindow()
{
    if(port->isOpen())
        port->close();
    delete port;
    delete ui;
}

void MainWindow::writeToUi(QString line)
{
    ui->textBrowser->append(line);
}
void MainWindow::onSerialReadyRead()
{
    QByteArray finalData;
    while(!port->atEnd())
    {
        QByteArray temp= port->read(100);
        finalData.append(temp);
    }
    writeToUi(finalData);

}

void MainWindow::onLog(QString log)
{
    writeToUi(log);
}

void MainWindow::onSerialDataAvailable(QString data)
{
    writeToUi(data);

}


void MainWindow::on_pushButton_clicked()
{
    QString portName=ui->comboBox->currentText();
    thread->init(portName);
    thread->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().size() > 0)
    {
        QString data = ui->lineEdit->text();
        thread->sendData(data+"\n");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    thread->toggle();
}
