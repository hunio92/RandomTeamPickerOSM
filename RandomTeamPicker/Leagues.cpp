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

/* Foreign header files */

/* Own header files */
#include "Leagues.h"

namespace randomTeamPicker
{
    namespace leaguesAndTeams
    {
        /*****************************************************************
         * CLASS GLOBAL DEFINITIONS
         *****************************************************************/

        /*****************************************************************
         * CLASS LOCAL DEFINITIONS
         *****************************************************************/

        /*****************************************************************
        * CLASS IMPLEMENTATION
         *****************************************************************/
        Leagues::Leagues()
        {

        }

        Leagues::~Leagues()
        {

        }

        void Leagues::addTeam(const QString teamName)
        {
            m_lTeamsName.append(teamName);
        }

        QStringList Leagues::getTeam() const
        {
            return m_lTeamsName;
        }

    } /* namespace leaguesAndTeams */
} /* namespace randomTeamPicker */
