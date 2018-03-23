#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager(const QString path)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);

    if( !database.open() )
    {
        qDebug() << "Error !";
    }
    else
    {
        qDebug() << "OK !";
    }
}

QStringList DbManager::getLeagues()
{
    return executeQuery("SELECT league_name FROM leagues");
}

QStringList DbManager::getTeams(const QString leagueName)
{
    return executeQuery("SELECT team_name FROM teams WHERE league_id = (SELECT league_id FROM leagues WHERE league_name = '" + leagueName + "')");
}

QStringList DbManager::executeQuery(const QString statement)
{
    QStringList lContainer;
    QSqlQuery query(statement);

    while(query.size() && query.next())
    {
        lContainer << query.value(0).toString();
    }

    return lContainer;
}
