#ifndef UTILITY_H
#define UTILITY_H

#include <QList>
#include <QCheckBox>
#include <QTextEdit>

class Utility : public QObject
{
public:
    Utility();
    void hideIfEmpty(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText, int sizeOfTeamList);
    void createCheckBoxAndEditBox(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText, QStringList &listOfTeams, int comboBoxHeight, QWidget* mainWindow);
//    void init_ItemModel(QTableView* pResultTableView);
private:
    void verifyCheckBoxState(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText);
    int m_nrOfActiveFields;
};

#endif // UTILITY_H
