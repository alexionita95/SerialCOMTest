#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "serialthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onSerialReadyRead();
    void onLog(QString log);
    void onSerialDataAvailable(QString data);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void writeToUi(QString line);
    Ui::MainWindow *ui;
    QSerialPort *port;
    SerialThread *thread;
};
#endif // MAINWINDOW_H
