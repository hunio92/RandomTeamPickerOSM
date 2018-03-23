#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>

class DbManager
{
    public:
        DbManager(const QString);
        QStringList getLeagues();
        QStringList getTeams(const QString leagueName);

    private:
        QStringList executeQuery(const QString statement);

};

#endif // DBMANAGER_H
