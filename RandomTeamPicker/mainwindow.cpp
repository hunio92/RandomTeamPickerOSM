#include "mainwindow.h"
#include "ui_mainwindow.h"

// *****************************************************************************************************
// * ToDo: checkbox and edittext disable from last, database and python script to get the update right *
// *****************************************************************************************************

qint64 processID;
QStringList listOfLeagues;
QStringList listOfTeams;
QList<QCheckBox*> lCheckBox;
QList<QTextEdit*> lEditText;
QList<QStandardItemModel*> lQStandardItem;
QFont defaultFont("Arial", 12, QFont::Bold);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(930, 950));

    m_DbManager = new DbManager("database.db");

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

    listOfLeagues = m_DbManager->getLeagues();

    for(int i = 0; i < listOfLeagues.size(); ++i)
    {
        ui->comboBoxLeagues->addItem(listOfLeagues.at(i));
    }
}

MainWindow::~MainWindow()
{
    // Kill process if called with startDetached App closed
//    QString pidString;
//    pidString.setNum(processID);
//    QString killProcessUsingPid = "taskkill /PID ";
//    killProcessUsingPid.append(pidString);
//    system(killProcessUsingPid.toStdString().c_str());

    delete ui;
}

// Check if ComboBox Changed
void MainWindow::on_comboBoxLeagues_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    // Check if Label or EditText is not empty if so hide and clear
    if(!lCheckBox.isEmpty() || !lEditText.isEmpty())
    {
        // Hide all old Labels and EditTexts
        for(int i = 0; i < listOfTeams.size(); ++i)
        {
            lCheckBox[i]->hide();
            lEditText[i]->hide();
        }

        // Clear lists
        lCheckBox.clear();
        lEditText.clear();
    }

    // Get selected item
    QString currentLeague = ui->comboBoxLeagues->currentText();
    // List of Teams
    listOfTeams = m_DbManager->getTeams(currentLeague);

    // Bottom, Top margin
    int margin = 10;
    // Height to position the Labels and editTexts
    int comboBoxHeight = ui->comboBoxLeagues->height() + margin;

    // Create as many EditText and Labels as teams are in the league
    for(int i = 0; i < listOfTeams.size(); ++i)
    {
        // Add EditTexts
        QTextEdit* pEditText = new QTextEdit(this);
        pEditText->setObjectName("PlayerEditTxt" + QString::number(i));
        pEditText->setText("");
        pEditText->move(this->width() * 0.01, comboBoxHeight * (3 + i));
        pEditText->setStyleSheet("QPlainTextEdit { margin:100; }");
        pEditText->setMinimumWidth(this->width() * 0.23);
        pEditText->show();
        lEditText.append(pEditText);

        QCheckBox *pCheckBox = new QCheckBox(this);
        pCheckBox->setObjectName("Label" + QString::number(i));
        pCheckBox->setText(listOfTeams[i]);
        pCheckBox->setChecked(true);
        pCheckBox->move(this->width() * 0.27, comboBoxHeight * (3 + i));
        pCheckBox->setFont(defaultFont);
        pCheckBox->setMinimumWidth(200);
        pCheckBox->show();
        lCheckBox.append(pCheckBox);

        connect(pCheckBox, &QCheckBox::stateChanged, [=]() mutable
        {
            if(pCheckBox->checkState() == 0)
            {
                lEditText[i]->setDisabled(true);
            }
            else if(pCheckBox->checkState() == 2)
            {
                lEditText[i]->setDisabled(false);
            }
        });
    }
}

void MainWindow::on_generateButton_clicked()
{
    // ****************************************************************
    // * ToDo: CLEAR RESULTS TABLE CORRECTLY NOT WITH: lQStandardItem *
    // ****************************************************************

    if(!lQStandardItem.isEmpty())
    {
        m_pItemModel = new QStandardItemModel();
        m_pItemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player names")));
        m_pItemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Team names")));
        m_pResultTableView->setModel(m_pItemModel);
    }

    QStringList listOfPlayers;
    QStringList tmpTeamList;
    for(int i = 0; i < lEditText.size(); ++i)
    {
        if(!lEditText[i]->toPlainText().isEmpty() && lEditText[i]->isEnabled())
        {
            listOfPlayers.append(lEditText[i]->toPlainText());
        }
        if(lCheckBox[i]->checkState() == 2)
        {
            tmpTeamList.append(lCheckBox[i]->text());
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
        lQStandardItem.append(m_pItemModel);

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
