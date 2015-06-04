#include "DatabaseAccessor.hpp"

#include "main.hpp"

#include <QSqlQuery>
#include <QSqlError>

#ifdef QT_DEBUG
#include <QDebug>
#endif

DatabaseAccessor::DatabaseAccessor(QObject *parent) :
    QObject(parent)
{
    if (initialize()) {
        createTables();
    }

#ifdef QT_DEBUG
    qDebug() << "Create DatabaseAccessor class";
#endif
}

DatabaseAccessor::~DatabaseAccessor()
{
    database.close();

#ifdef QT_DEBUG
    qDebug() << "Destroy DatabaseAccessor class";
#endif
}

void DatabaseAccessor::execute(const QString &query)
{
    QList<QSqlRecord> recordList;
    QSqlQuery q(database);

    if (!q.exec(query)) {
#ifdef QT_DEBUG
        qDebug() << "Failed to execute SQL query:" << q.lastError().text();
#endif

        return;
    } else {
        while (q.next()) {
            recordList.append(q.record());
        }
    }

    emit results(recordList);
}

void DatabaseAccessor::execute(const QList<QString> &queryList)
{
    if (!database.transaction()) {
#ifdef QT_DEBUG
        qDebug() << "Database transaction error:" << database.lastError().text();
#endif

        return;
    }

    QList<QSqlRecord> recordList;
    QSqlQuery q(database);

    for (int i = 0; i < queryList.count(); ++i) {
        if (!q.exec(queryList.at(i))) {
#ifdef QT_DEBUG
            qDebug() << "Failed to execute SQL query:" << q.lastError().text();
#endif

            continue;
        } else {
            while (q.next()) {
                recordList.append(q.record());
            }
        }
    }

    if (!database.commit()) {
#ifdef QT_DEBUG
        qDebug() << "Database commit error:" << database.lastError().text();
#endif

        return;
    }

    emit results(recordList);
}

bool DatabaseAccessor::initialize()
{
    database = QSqlDatabase::addDatabase(DATABASE_DRIVER, "DatabaseAccessor");
    database.setDatabaseName(DATABASE_NAME);
    database.setHostName(DATABASE_HOST);
    database.setUserName(DATABASE_USER);
    database.setPassword(DATABASE_PASS);

    if (!database.open()) {
#ifdef QT_DEBUG
        qDebug() << "Unable to connect to database, giving up:" << database.lastError().text();
#endif

        return false;
    }

    return true;
}

void DatabaseAccessor::createTables()
{
    createTableAccounts();
    createTableFiles();
}

void DatabaseAccessor::createTableAccounts()
{
    if (database.tables().contains("montnium_accounts")) {
        return;
    }

    QStringList queryList;
    queryList.append("CREATE TABLE montnium_accounts ("
                     "  id Integer NOT NULL PRIMARY KEY,"
                     "  email Text NOT NULL,"
                     "  password Text DEFAULT NULL,"
                     "  first_name Text DEFAULT NULL,"
                     "  last_name Text DEFAULT NULL,"
                     "  profile_url Text DEFAULT NULL,"

                     "  verified Text DEFAULT NULL,"
                     "  status Text DEFAULT NULL,"
                     "  created Text DEFAULT NULL,"
                     "  expiration Text DEFAULT NULL,"
                     "  last_login Text DEFAULT NULL,"

                     "  free_space Integer DEFAULT 0,"
                     "  total_space Integer DEFAULT 0,"
                     "  upload_size_limit Integer DEFAULT 0,"
                     "  files_count Integer DEFAULT 0,"
                     "  downloads_count Integer DEFAULT 0,"

                     "  relevant_content_off Text DEFAULT NULL,"
                     "  allow_search_account Text DEFAULT NULL,"
                     "  disable_all_comments Text DEFAULT NULL,"
                     " CONSTRAINT unique_email UNIQUE (email)"
                     ");");

    queryList.append("CREATE INDEX index_accounts_email ON montnium_accounts (email);");
    queryList.append("CREATE INDEX index_accounts_files_count ON montnium_accounts (files_count);");
    queryList.append("CREATE INDEX index_accounts_downloads_count ON montnium_accounts (downloads_count);");

    QSqlQuery q(database);

    for (int i = 0; i < queryList.count(); ++i) {
        if (!q.exec(queryList.at(i).toLocal8Bit().constData())) {
#ifdef QT_DEBUG
            qDebug() << "Failed to create table:" << q.lastError().text();
#endif

            continue;
        }
    }
}

void DatabaseAccessor::createTableFiles()
{
    if (database.tables().contains("montnium_files")) {
        return;
    }

    QStringList queryList;
    queryList.append("CREATE TABLE montnium_files ("
                     "  id Integer NOT NULL PRIMARY KEY,"
                     "  account_parent Integer DEFAULT 0,"
                     "  name Text NOT NULL,"
                     "  size Integer DEFAULT 0,"
                     "  download_time Text DEFAULT NULL,"
                     "  download_count Integer DEFAULT 0,"
                     "  url Text DEFAULT NULL"
                     ");");

    queryList.append("CREATE INDEX index_files_account_parent ON montnium_files (account_parent);");
    queryList.append("CREATE INDEX index_files_download_count ON montnium_files (download_count);");

    QSqlQuery q(database);

    for (int i = 0; i < queryList.count(); ++i) {
        if (!q.exec(queryList.at(i).toLocal8Bit().constData())) {
#ifdef QT_DEBUG
            qDebug() << "Failed to create table:" << q.lastError().text();
#endif

            continue;
        }
    }
}
