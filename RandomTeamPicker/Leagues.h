#ifndef LEAGUES
#define LEAGUES

/**
 * @file   leagues.h
 * @brief  Contain Leagues
 * @author Hunor Orban
 * @date   2018-01-31
 */

/*****************************************************************
 ** Header Files
 *****************************************************************/

/* System header files */
#include <QString>
#include <QStringList>
#include <QMap>

/* Foreign header files */

/* Own header files */

/* Forward declarations of types */

/*****************************************************************
 ** Namespace to which this class belongs to
 *****************************************************************/
namespace randomTeamPicker
{
    namespace leaguesAndTeams
    {
        /*****************************************************************
        * Definition of exported global data used by Class
        * Macros, Enumerations, Types,  Forward declarations
        *****************************************************************/

        struct OSM
        {
            QStringList Leagues;
            QMap<QString, QStringList> LeagueAndTeams;
        };

        /*****************************************************************
         * CLASS DEFINITION
         *****************************************************************/
        /**
         * @class   ExportRodsToXml
         * @brief   Contain Leagues and Teams
         */
        class Leagues
        {
                public:
                /** public methods */

                /**
                 * @brief Constructor
                */
                Leagues();

                /**
                 * @brief Destructor
                 */
                virtual ~Leagues();

                /** public attributes (not recommended!) */

                /**
                 * @brief Add a new team to list
                */
                void addTeam(const QString teamName);

                /**
                 * @brief Get the list of teams
                */
                QStringList getTeam() const;

                protected:
                /** protected methods */

                /** protected attributes */

                private:
                /** private methods */

                /** private attributes */
                QStringList m_lTeamsName;
        };
    } /* namespace leaguesAndTeams */
} /* namespace randomTeamPicker */

#endif // LEAGUES

