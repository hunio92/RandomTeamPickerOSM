#include "mainwindow.h"
#include "ui_mainwindow.h"

struct OSM
{
    QStringList Leagues;
    QMap<QString, QStringList> LeagueAndTeams;
};

OSM leagues;
QStringList listOfTeams;
QList<QLabel*> lLabel;
QList<QTextEdit*> lEditText;
QFont defaultFont("Arial", 12, QFont::Bold);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(930, 950));

    QIcon icon(":/images/randomIcon.ico");
    this->setWindowIcon(icon);

    // ComboBox Leagues
    ui->comboBoxLeagues->setGeometry(QRect(this->width() * 0.20, this->height() * 0.01, 100, 30));
    ui->comboBoxLeagues->setFont(defaultFont);

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

    leagues.Leagues.append("England");
    leagues.Leagues.append("Spain");
    leagues.Leagues.append("Italy");

    // England
    QStringList lEnglandTeams;
    lEnglandTeams.append("Chelsea");
    lEnglandTeams.append("Manchester City");
    lEnglandTeams.append("Manchester United");
    lEnglandTeams.append("Arsenal");
    lEnglandTeams.append("Liverpool");
    lEnglandTeams.append("Tottenham Hotspur");
    lEnglandTeams.append("Everton");
    lEnglandTeams.append("Leicester City");
    lEnglandTeams.append("Southampton");
    lEnglandTeams.append("West Ham United");
    lEnglandTeams.append("Crystal Palace");
    lEnglandTeams.append("Stoke City");
    lEnglandTeams.append("Watford");
    lEnglandTeams.append("West Bromwich Albion");
    lEnglandTeams.append("Burnley");
    lEnglandTeams.append("Newcastle United");
    lEnglandTeams.append("Swansea City");
    lEnglandTeams.append("Bournemouth");
    lEnglandTeams.append("Brighton and Hove Albion");
    lEnglandTeams.append("Huddersfield Town");

    // Spain
    QStringList lSpainTeams;
    lSpainTeams.append("Barcelona");
    lSpainTeams.append("Real Madrid");
    lSpainTeams.append("Atlético Madrid");
    lSpainTeams.append("Sevilla");
    lSpainTeams.append("Valencia");
    lSpainTeams.append("Athletic Bilbao");
    lSpainTeams.append("Villarreal");
    lSpainTeams.append("Celta de Vigo");
    lSpainTeams.append("Real Sociedad");
    lSpainTeams.append("Deportivo La Coruña");
    lSpainTeams.append("Eibar");
    lSpainTeams.append("Espanyol");
    lSpainTeams.append("Málaga");
    lSpainTeams.append("Real Betis");
    lSpainTeams.append("Girona");
    lSpainTeams.append("Leganés");
    lSpainTeams.append("Alavés");
    lSpainTeams.append("Getafe");
    lSpainTeams.append("Las Palmas");
    lSpainTeams.append("Levante");

    // Italy
    QStringList lItalyTeams;
    lItalyTeams.append("Juventus");
    lItalyTeams.append("Napoli");
    lItalyTeams.append("Roma");
    lItalyTeams.append("AC Milan");
    lItalyTeams.append("Inter Milan");
    lItalyTeams.append("Lazio");
    lItalyTeams.append("Fiorentina");
    lItalyTeams.append("Atalanta");
    lItalyTeams.append("Sampdoria");
    lItalyTeams.append("Torino");
    lItalyTeams.append("Bologna");
    lItalyTeams.append("Genoa");
    lItalyTeams.append("Sassuolo");
    lItalyTeams.append("Udinese");
    lItalyTeams.append("Cagliari");
    lItalyTeams.append("Chievo");
    lItalyTeams.append("Verona");
    lItalyTeams.append("Benevento");
    lItalyTeams.append("Crotone");
    lItalyTeams.append("SPAL");

    leagues.LeagueAndTeams.insert(leagues.Leagues.at(0), lEnglandTeams);
    leagues.LeagueAndTeams.insert(leagues.Leagues.at(1), lSpainTeams);
    leagues.LeagueAndTeams.insert(leagues.Leagues.at(2), lItalyTeams);

    for(int i = 0; i < leagues.Leagues.size(); ++i)
    {
        ui->comboBoxLeagues->addItem(leagues.Leagues.at(i));
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

    // Check if Label or EditText is not empty if so hide and clear
    if(!lLabel.isEmpty() || !lEditText.isEmpty())
    {
        // Hide all old Labels and EditTexts
        for(int i = 0; i < listOfTeams.size(); ++i)
        {
            lLabel[i]->hide();
            lEditText[i]->hide();
        }

        // Clear lists
        lLabel.clear();
        lEditText.clear();
    }

    // Get selected item
    QString currentLeague = ui->comboBoxLeagues->currentText();
    // List of Teams
    listOfTeams = leagues.LeagueAndTeams.value(currentLeague);

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

        // Add Labels
        QLabel* pLabel = new QLabel(this);
        pLabel->setObjectName("Label" + QString::number(i));
        pLabel->setText(listOfTeams[i]);
        pLabel->move(this->width() * 0.27, comboBoxHeight * (3 + i));
        pLabel->setFont(defaultFont);
        pLabel->setMinimumWidth(200);
        pLabel->show();
        lLabel.append(pLabel);
    }
}

void MainWindow::on_generateButton_clicked()
{
    // *****************************
    // * ToDo: CLEAR RESULTS TABLE *
    // *****************************

    QStringList listOfPlayers;
    for(int i = 0; i < lEditText.size(); ++i)
    {
        if(!lEditText[i]->toPlainText().isEmpty())
        {
            listOfPlayers.append(lEditText[i]->toPlainText());
        }
    }

    int randPlayer = 0, randTeam = 0, rowIndex = 0;
    QStringList tmpTeamList;
    tmpTeamList = listOfTeams;

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
