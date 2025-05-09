#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QRegularExpression>

void loadEnv()
{
    QString envPath = QCoreApplication::applicationDirPath() + "/.env";
    QFile envFile(envPath);

    // Check if the .env file exists
    if (!envFile.exists()) {
        qDebug() << "Couldn't find .env file at" << envPath;
        return;
    }

    // Open the file in read-only and text mode
    if (!envFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Couldn't open .env file!";
        return;
    }

    QTextStream in(&envFile);

    // Read the file line by line
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Skip empty lines and comments
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }

        // Split the line into key-value pairs based on the '=' character
        QStringList keyValue = line.split('=', Qt::KeepEmptyParts);
        if (keyValue.size() == 2) {
            QString key = keyValue.at(0).trimmed();
            QString value = keyValue.at(1).trimmed();

            // Remove surrounding quotes if present using QRegularExpression
            QRegularExpression regex("^\"|\"$");
            value.remove(regex);

            // Log the loaded environment variable
            qDebug() << "Loaded environment variable:" << key << "=" << value;

            // Set the environment variable
            qputenv(key.toUtf8(), value.toUtf8());
        } else {
            // Handle invalid lines in the .env file
            qDebug() << "Invalid line in .env file:" << line;
        }
    }

    // Close the file
    envFile.close();

    // Log the environment variables after loading
    qDebug() << "SENDGRID_API_KEY:" << qgetenv("SENDGRID_API_KEY");
    qDebug() << "SENDGRID_SENDER_EMAIL:" << qgetenv("SENDGRID_SENDER_EMAIL");

    // Log completion message
    qDebug() << ".env variables loaded from" << envPath;
}
