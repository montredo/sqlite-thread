#include "DatabaseThread.hpp"
#include "DatabaseAccessor.hpp"

#ifdef QT_DEBUG
#include <QDebug>
#endif

DatabaseThread::DatabaseThread(QObject *parent) :
    QThread(parent)
{
#ifdef QT_DEBUG
    qDebug() << "Create DatabaseThread class";
#endif
}

DatabaseThread::~DatabaseThread()
{
    delete accessor;

#ifdef QT_DEBUG
    qDebug() << "Destroy DatabaseThread class";
#endif
}

void DatabaseThread::run()
{
    accessor = new DatabaseAccessor;

    connect(this, SIGNAL(execute(QString)), accessor, SLOT(execute(QString)));
    connect(this, SIGNAL(execute(QList<QString>)), accessor, SLOT(execute(QList<QString>)));

    tests();

    exec();
}

void DatabaseThread::tests()
{
    for (int i = 0; i < 100; ++i) {
        QString value = "dasdas";
        QString query = QString("INSERT INTO montnium_accounts (email) VALUES ('%1_%2');").arg(value).arg(i + 1);

        emit execute(query);
    }
}
