#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class ArduinoInterface : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoInterface(QObject *parent = nullptr);
    ~ArduinoInterface();


    bool connectPort(int baud = 9600);
    void disconnectPort();

    void sendMuteCommand();
    void sendUnmuteCommand();

    void sendSmokeOn();
    void sendSmokeOff();
    void sendGentleOn();
    void sendGentleOff();

    void resetSmokeNotification();

signals:
    void smokeDetected();
    void error(const QString &msg);

private slots:
    void handleReadyRead();

private:
    QSerialPort *serial;
    QByteArray    buffer;

    QString autoDetectPort();

    bool smokeNotified;
};

#endif // ARDUINOINTERFACE_H
