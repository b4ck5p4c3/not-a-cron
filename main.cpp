#include <QCommandLineParser>
#include <QCoreApplication>
#include <QObject>
#include <QProcess>

#include <QDebug>

#include "qcron.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("not-a-cron"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.0.1"));

    QCommandLineParser parser;
    parser.setApplicationDescription("Not a cron");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption patternOption(QStringList() << QStringLiteral("pattern"),
                                     QCoreApplication::translate("main", "cron syntax pattern"),
                                     QCoreApplication::translate("main", "cron-pattern"));
    parser.addOption(patternOption);
    QCommandLineOption activatedOption(QStringList() << QStringLiteral("on-activated"),
                                       QCoreApplication::translate("main", "command on activated"),
                                       QCoreApplication::translate("main", "command"));
    parser.addOption(activatedOption);
    QCommandLineOption deactivatedOption(QStringList() << QStringLiteral("on-deactivated"),
                                         QCoreApplication::translate("main", "command on deactivated"),
                                         QCoreApplication::translate("main", "command"));
    parser.addOption(deactivatedOption);
    parser.process(a);

    QString pattern = parser.value(patternOption);

    qDebug() << "starting application with pattern" << pattern;

    QCron cron(pattern);

    if (!cron.isValid()) {
        qDebug() << "not valid pattern";
        return -1;
    }

    QString activatedCommand = parser.value(activatedOption);
    if (!activatedCommand.isEmpty()) {
        qDebug() << "qcron activate command:" << cron.next() << activatedCommand;
        QObject::connect(&cron, &QCron::activated, [activatedCommand](){
            QProcess process;
            QStringList args = process.splitCommand(activatedCommand);
            const QString program = args.takeFirst();
            qDebug() << "qcron activated with" << program << ":" << args;
            process.setProgram(program);
            process.setArguments(args);
            process.startDetached();
        });
    }

    QString deactivatedCommand = parser.value(deactivatedOption);
    if (!deactivatedCommand.isEmpty()) {
        qDebug() << "qcron deactivate command:" << cron.next() << deactivatedCommand;
        QObject::connect(&cron, &QCron::deactivated, [deactivatedCommand](){
            QProcess process;
            QStringList args = process.splitCommand(deactivatedCommand);
            const QString program = args.takeFirst();
            qDebug() << "qcron activated with" << program << ":" << args;
            process.setProgram(program);
            process.setArguments(args);
            process.startDetached();
        });
    }

    return a.exec();
}
