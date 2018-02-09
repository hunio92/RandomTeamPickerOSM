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

private:
    Ui::MainWindow *ui;

    QTableView *m_pResultTableView;
    QStandardItemModel *m_pItemModel;
};

#endif // MAINWINDOW_H
