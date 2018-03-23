#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextEdit>
#include <QLabel>
#include <QRectF>
#include <QTableView>
#include <QStandardItemModel>
#include <QProcess>
#include <QDir>
#include <QMovie>
#include <QCheckBox>
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_comboBoxLeagues_currentIndexChanged(int index);

    void on_generateButton_clicked();

    void on_updateButton_clicked();

protected:
//    friend class QProcess;

private:
    Ui::MainWindow *ui;

    QTableView *m_pResultTableView;
    QStandardItemModel *m_pItemModel;
    DbManager* m_DbManager;
};

#endif // MAINWINDOW_H
