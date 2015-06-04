#ifndef DATABASEACCESSOR_HPP
#define DATABASEACCESSOR_HPP

#include <QObject>

#include <QSqlDatabase>
#include <QSqlRecord>

class DatabaseAccessor : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseAccessor(QObject *parent = 0);
    ~DatabaseAccessor();

signals:
    void results(const QList<QSqlRecord> &recordList);

public slots:
    void execute(const QString &query);
    void execute(const QList<QString> &queryList);

private:
    bool initialize();

    void createTables();
    void createTableAccounts();
    void createTableFiles();

    QSqlDatabase database;
};

#endif // DATABASEACCESSOR_HPP
