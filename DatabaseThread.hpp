#ifndef DATABASETHREAD_HPP
#define DATABASETHREAD_HPP

#include <QThread>

class DatabaseAccessor;

class DatabaseThread : public QThread
{
    Q_OBJECT
public:
    DatabaseThread(QObject *parent = 0);
    ~DatabaseThread();

signals:
    void execute(const QString &query);
    void execute(const QList<QString> &queryList);

protected:
    void run();

private:
    void tests();

    DatabaseAccessor *accessor;
};

#endif // DATABASETHREAD_HPP
