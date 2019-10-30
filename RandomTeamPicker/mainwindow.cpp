#include "mainwindow.h"
#include "ui_mainwindow.h"

// *****************************************************************************************************
// * ToDo: database and python script to get the update right *
// * BUG: chenck/uncheck checkbox then switch league will continue where was *
// *****************************************************************************************************

QFont defaultFont("Arial", 12, QFont::Bold);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_listOfLeagues(),
    m_listOfTeams()
{
    ui->setupUi(this);
    this->setFixedSize(QSize(930, 820));

    m_DbManager = new DbManager("database.db");
    m_Utility = new Utility();

    QIcon icon(":/images/randomIcon.ico");
    this->setWindowIcon(icon);

    // ComboBox Leagues
    ui->comboBoxLeagues->setGeometry(QRect(this->width() * 0.20, this->height() * 0.01, 260, 30));
    ui->comboBoxLeagues->setFont(defaultFont);

    // Push Button Update leagues
    ui->updateButton->setGeometry(QRect(this->width() * 0.01, this->height() * 0.01, 150, 30));
    ui->updateButton->setFont(defaultFont);

    // Push Button Generate
    ui->generateButton->setGeometry(QRect(this->width() * 0.70, this->height() * 0.01, 100, 30));
    ui->generateButton->setFont(defaultFont);

    // Vertical Line separate in half the main window
    QFrame *lineSplitInHalf = new QFrame(this);
    lineSplitInHalf->setObjectName(QString::fromUtf8("lineSplitInHalf"));
    lineSplitInHalf->setGeometry(QRect(this->width() * 0.5, 0, 5, this->height()));
    lineSplitInHalf->setFrameShape(QFrame::VLine);
    lineSplitInHalf->setFrameShadow(QFrame::Sunken);

    // Vertical Line separate player box from team label
    QFrame *linePlayersTeams = new QFrame(this);
    linePlayersTeams->setObjectName(QString::fromUtf8("linePlayersTeams"));
    linePlayersTeams->setGeometry(QRect(this->width() * 0.25, ui->comboBoxLeagues->height() * 2, 5, this->height()));
    linePlayersTeams->setFrameShape(QFrame::VLine);
    linePlayersTeams->setFrameShadow(QFrame::Sunken);

    // Players Text
    QLabel* pLabelPlayerTxt = new QLabel(this);
    pLabelPlayerTxt->setObjectName("labelPlayerText");
    pLabelPlayerTxt->setText("Players");
    pLabelPlayerTxt->move(this->width() * 0.10,  ui->comboBoxLeagues->height() * 2);
    pLabelPlayerTxt->setFont(defaultFont);
    pLabelPlayerTxt->setStyleSheet("QLabel { text-decoration: underline; }");

    //Teams Text
    QLabel* pLabelTeamTxt = new QLabel(this);
    pLabelTeamTxt->setObjectName("labelTeamText");
    pLabelTeamTxt->setText("Teams");
    pLabelTeamTxt->move(this->width() * 0.35,  ui->comboBoxLeagues->height() * 2);
    pLabelTeamTxt->setFont(defaultFont);
    pLabelTeamTxt->setStyleSheet("QLabel { text-decoration: underline; }");

    //Results Text
    QLabel* pLabelResultsTxt = new QLabel(this);
    pLabelResultsTxt->setObjectName("labelResultsText");
    pLabelResultsTxt->setText("Results");
    pLabelResultsTxt->move(this->width() * 0.72,  ui->comboBoxLeagues->height() * 2);
    pLabelResultsTxt->setFont(defaultFont);
    pLabelResultsTxt->setStyleSheet("QLabel { text-decoration: underline; }");

    // Results Table
    m_pItemModel = new QStandardItemModel();
    m_pItemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player names")));
    m_pItemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Team names")));

    m_pResultTableView = new QTableView(this);
    m_pResultTableView->setGeometry(QRect(this->width() * 0.51, ui->comboBoxLeagues->height() * 4, this->width() * 0.48, this->height() * 0.87));
    m_pResultTableView->setModel(m_pItemModel);
    m_pResultTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pResultTableView->setColumnWidth(0, m_pResultTableView->width() * 0.50);
    m_pResultTableView->setColumnWidth(1, m_pResultTableView->width() * 0.50);
    m_pResultTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_pResultTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pResultTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pResultTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_listOfLeagues = m_DbManager->getLeagues();

    for(int i = 0; i < m_listOfLeagues.size(); ++i)
    {
        ui->comboBoxLeagues->addItem(m_listOfLeagues.at(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Check if ComboBox Changed
void MainWindow::on_comboBoxLeagues_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    // When switch the team, hide unused CheckBoxes and EditTexts
    m_Utility->hideIfEmpty(m_lCheckBox, m_lEditText, m_listOfTeams.size());

    // Get selected item
    QString currentLeague = ui->comboBoxLeagues->currentText();
    // List of Teams
    m_listOfTeams = m_DbManager->getTeams(currentLeague);

    // Height to position the Labels and editTexts
    int comboBoxHeight = ui->comboBoxLeagues->height() + 5;

    // Create EditTests and popultea CheckBoxes with teams
    m_Utility->createCheckBoxAndEditBox(m_lCheckBox, m_lEditText, m_listOfTeams, comboBoxHeight, this);
}

void MainWindow::on_generateButton_clicked()
{
    m_pItemModel = new QStandardItemModel();
    m_pItemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player names")));
    m_pItemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Team names")));
    m_pResultTableView->setModel(m_pItemModel);

//    m_Utility->init_ItemModel(m_pResultTableView);

    QStringList listOfPlayers;
    QStringList tmpTeamList;
    for(int i = 0; i < m_lEditText.size(); ++i)
    {
        if(!m_lEditText[i]->toPlainText().isEmpty() && m_lEditText[i]->isEnabled())
        {
            listOfPlayers.append(m_lEditText[i]->toPlainText());
        }
        if(m_lCheckBox[i]->checkState() == 2)
        {
            tmpTeamList.append(m_lCheckBox[i]->text());
        }
    }

    int randPlayer = 0, randTeam = 0, rowIndex = 0;

    while (listOfPlayers.size() > 0)
    {
        randPlayer = qrand() % listOfPlayers.size();
        randTeam = qrand() % tmpTeamList.size();

        QStandardItem *tmpPlayerItem = new QStandardItem(listOfPlayers.at(randPlayer));
        m_pItemModel->setItem(rowIndex, 0, tmpPlayerItem);
        QStandardItem *tmpTeamItem = new QStandardItem(tmpTeamList.at(randTeam));
        m_pItemModel->setItem(rowIndex, 1, tmpTeamItem);

        if(rowIndex % 2 != 0)
        {
            tmpPlayerItem->setBackground(QBrush(QColor(220,220,220)));
            tmpTeamItem->setBackground(QBrush(QColor(220,220,220)));
        }
        else
        {
            tmpPlayerItem->setBackground(QBrush(QColor(192,192,192)));
            tmpTeamItem->setBackground(QBrush(QColor(192,192,192)));
        }

        listOfPlayers.removeAt(randPlayer);
        tmpTeamList.removeAt(randTeam);
        ++rowIndex;
    }
}

void MainWindow::on_updateButton_clicked()
{
    QMovie *movie = new QMovie(":/images/please_wait.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setGeometry(QRect(this->width() * 0.35, this->height() * 0.35, 265, 120));
    processLabel->setMovie(movie);
    processLabel->show();
    movie->start();

    this->setDisabled(true);

    QString path = QCoreApplication::applicationDirPath();
    QString  command("python");
    QStringList params = QStringList() << "GetLeaguesAndTeams.py";

    QProcess *process = new QProcess();
    process->setWorkingDirectory(path);
    //    process->startDetached(command, params, path, &processID);
    process->start(command, params);
    process->waitForStarted();
    connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), [=]()
    {
        movie->stop();
        processLabel->hide();
        this->setDisabled(false);
        process->close();
    });
}
