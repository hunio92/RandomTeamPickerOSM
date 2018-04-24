#include "utility.h"
#include <QDebug>

Utility::Utility()
{

}

void Utility::hideIfEmpty(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText, int sizeOfTeamList)
{
    // Check if Label or EditText is not empty if so hide and clear
    if(!lCheckBox.isEmpty() || !lEditText.isEmpty())
    {
        // Hide all old Labels and EditTexts
        for(int i = 0; i < sizeOfTeamList; ++i)
        {
            lCheckBox[i]->hide();
            lEditText[i]->hide();
        }

        // Clear lists
        lCheckBox.clear();
        lEditText.clear();
    }
}

void Utility::verifyCheckBoxState(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText)
{
    for(int i = 0; i < lCheckBox.size(); ++i)
    {
        // Verify the state of the checkboxes
        connect(lCheckBox[i], &QCheckBox::stateChanged, [=]()
        {
            if(lCheckBox[i]->checkState() == 0)
            {
                --m_nrOfActiveFields;
                lEditText[m_nrOfActiveFields]->setDisabled(true);
            }
            else if(lCheckBox[i]->checkState() == 2)
            {
                lEditText[m_nrOfActiveFields]->setDisabled(false);
                ++m_nrOfActiveFields;
            }
            qDebug() << m_nrOfActiveFields;
        });
    }
}

void Utility::createCheckBoxAndEditBox(QList<QCheckBox*> &lCheckBox, QList<QTextEdit*> &lEditText, QStringList &listOfTeams, int comboBoxHeight, QWidget* mainWindow)
{
    QFont defaultFont("Arial", 12, QFont::Bold);
    // Create as many EditText and Labels as teams are in the league
    for(int i = 0; i < listOfTeams.size(); ++i)
    {
        // Add new EditTexts
        QTextEdit* pEditText = new QTextEdit(mainWindow);
        pEditText->setObjectName("PlayerEditTxt" + QString::number(i));
        pEditText->setText("");
        pEditText->move(mainWindow->width() * 0.01, comboBoxHeight * (3 + i));
        pEditText->setStyleSheet("QPlainTextEdit { margin:100; }");
        pEditText->setMinimumWidth(mainWindow->width() * 0.23);
        pEditText->show();
        lEditText.append(pEditText);

        // Add new CheckBox
        QCheckBox *pCheckBox = new QCheckBox(mainWindow);
        pCheckBox->setObjectName("Label" + QString::number(i));
        pCheckBox->setText(listOfTeams[i]);
        pCheckBox->setChecked(true);
        pCheckBox->move(mainWindow->width() * 0.27, comboBoxHeight * (3 + i));
        pCheckBox->setFont(defaultFont);
        pCheckBox->setMinimumWidth(200);
        pCheckBox->show();
        lCheckBox.append(pCheckBox);
    }

    m_nrOfActiveFields = lCheckBox.size();
    Utility::verifyCheckBoxState(lCheckBox, lEditText);
}

// ################ init_ItemModel create !

//void Utility::init_ItemModel(QTableView* pResultTableView)
//{
//    pItemModel = new QStandardItemModel();
//    pItemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player names")));
//    pItemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Team names")));
//    pResultTableView->setModel(pItemModel);
//}
