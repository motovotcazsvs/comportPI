#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

        serial = new QSerialPort;

        //serial->setPortName("/dev/ttyUSB0"); // GPIO
        serial->setPortName("/dev/ttyS0");

        //serial->setBaudRate(QSerialPort::Baud9600);
        serial->setBaudRate(QSerialPort::Baud115200);

        serial->setDataBits(QSerialPort::Data8);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop); // Is this correct?

        if (!serial->open(QIODevice::ReadWrite))
        {
            qDebug() << "dispenseThread::run: ERROR: Cannot open serial port!";
            qDebug() << serial->errorString();
        }

        connect(serial, &QSerialPort::readyRead, this, &MainWindow::readslot);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::on_pushButton_clicked()
{


}

void MainWindow::readslot()
{
    QByteArray responseData = serial->readAll();
    //const QString response2 = QString::fromUtf8(resp);
    while (serial->waitForReadyRead(10))
    {
        responseData += serial->readAll();
    }
    qDebug() << responseData;

}

void MainWindow::on_pushButton_2_clicked()
{
    if(serial->isOpen() == true){
        serial->write("hello");
        serial->write("vova");
        qDebug() << "write uart";
    }
}
