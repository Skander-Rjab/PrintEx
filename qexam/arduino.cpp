#include "arduino.h"
#include <QDebug>


static const char SMOKE_ON_CMD[]    = "SMOKE_ON\n";
static const char SMOKE_OFF_CMD[]   = "SMOKE_OFF\n";
static const char GENTLE_ON_CMD[]   = "GENTLE_ON\n";
static const char GENTLE_OFF_CMD[]  = "GENTLE_OFF\n";
static const char MUTE_CMD[]        = "MUTE\n";
static const char UNMUTE_CMD[]      = "UNMUTE\n";

ArduinoInterface::ArduinoInterface(QObject *parent)
    : QObject(parent),
    serial(new QSerialPort(this)),
    smokeNotified(false)
{
    connect(serial, &QSerialPort::readyRead,
            this, &ArduinoInterface::handleReadyRead);
}

ArduinoInterface::~ArduinoInterface()
{
    disconnectPort();
}

bool ArduinoInterface::connectPort(int baud)
{
    QString portName = autoDetectPort();

    smokeNotified = false;

    if (portName.isEmpty()) {
        emit error("No Arduino-compatible port found.");
        return false;
    }

    serial->setPortName(portName);
    if (!serial->open(QIODevice::ReadWrite)) {
        emit error(QString("Failed to open port %1").arg(portName));
        return false;
    }

    serial->setBaudRate(baud);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);


    qDebug() << "Connected to Arduino on port" << portName;
    return true;
}

void ArduinoInterface::disconnectPort()
{
    if (serial->isOpen())
        serial->close();
}

void ArduinoInterface::sendMuteCommand()   //write
{
    if (serial->isOpen())
        serial->write(MUTE_CMD);
}

void ArduinoInterface::sendUnmuteCommand()    //write
{
    if (serial->isOpen())
        serial->write(UNMUTE_CMD);
}

void ArduinoInterface::sendSmokeOn()        { if(serial->isOpen()) serial->write(SMOKE_ON_CMD); }
void ArduinoInterface::sendSmokeOff()       { if(serial->isOpen()) serial->write(SMOKE_OFF_CMD); }


void ArduinoInterface::sendGentleOn()       { if(serial->isOpen()) serial->write(GENTLE_ON_CMD); }
void ArduinoInterface::sendGentleOff()      { if(serial->isOpen()) serial->write(GENTLE_OFF_CMD); }

void ArduinoInterface::handleReadyRead() {
    buffer.append(serial->readAll());
    int idx;
    while ((idx = buffer.indexOf('\n')) != -1) {
        QString line = QString::fromUtf8(buffer.left(idx)).trimmed();
        buffer.remove(0, idx+1);
        qDebug() << "[Arduino] RX:" << line;
        if (line == "SMOKE" && !smokeNotified) {
            smokeNotified = true;
            emit smokeDetected();
        }
    }
}

void ArduinoInterface::resetSmokeNotification()
{
    smokeNotified = false;
}

QString ArduinoInterface::autoDetectPort()
{

    const struct { quint16 vid, pid; } knownIds[] = {
        {0x2341, 0x0043},
        {0x2341, 0x0001},
        {0x2A03, 0x0043},
        {0x0403, 0x6001},
        {0x1A86, 0x7523},
        {0x10C4, 0xEA60},
    };
    const int knownCount = sizeof(knownIds) / sizeof(knownIds[0]);


    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < ports.size(); ++i) {
        const QSerialPortInfo &info = ports.at(i);
        if (!info.hasVendorIdentifier() || !info.hasProductIdentifier())
            continue;


        for (int j = 0; j < knownCount; ++j) {
            if (info.vendorIdentifier() == knownIds[j].vid &&
                info.productIdentifier() == knownIds[j].pid)
            {
                qDebug() << "Found Arduino on" << info.portName()
                << "(VID" << QString::number(knownIds[j].vid,16)
                << "PID" << QString::number(knownIds[j].pid,16) << ")";
                return info.portName();
            }
        }
    }

    return QString();
}
