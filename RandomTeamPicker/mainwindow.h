#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QTextEdit>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include <QMovie>
#include <QCheckBox>
#include "dbmanager.h"
#include "utility.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList m_listOfLeagues;
    QStringList m_listOfTeams;
    QList<QCheckBox*> m_lCheckBox;
    QList<QTextEdit*> m_lEditText;

private slots:

    void on_comboBoxLeagues_currentIndexChanged(int index);

    void on_generateButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::MainWindow* ui;

    QTableView* m_pResultTableView;
    QStandardItemModel* m_pItemModel;
    DbManager* m_DbManager;
    Utility* m_Utility;
};

#endif // MAINWINDOW_H
