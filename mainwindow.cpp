#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Labyrinth.h"
#include "GameStatistic.h"
//================================================================================================================
#include <QKeyEvent>
#include <QString>
#include <QDebug>
//================================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_pqpbNewGame, SIGNAL(clicked()), this, SLOT(slotNewGame()));
    ui->m_pqpbNewGame->setFocusPolicy(Qt::NoFocus);
    ui->m_pqpbNewGame->setVisible(false);
    m_pGameStatistic = new GameStatistic();
    const int  CODE_OWNER_OF_BULLETS_OF_ALIENS = 13;
    Labyrinth::SetInternalStaticVariables(m_pGameStatistic, CODE_OWNER_OF_BULLETS_OF_ALIENS);
    SetGame();
}
//================================================================================================================
MainWindow::~MainWindow()
{
    delete ui;
    if (nullptr != m_pLabyrinth) {
        delete m_pLabyrinth;
    }
    if (nullptr != m_pGameStatistic) {
        delete m_pGameStatistic;
    }
}
//================================================================================================================
void MainWindow::slotGameOver()
{
    delete m_pLabyrinth;
    m_pLabyrinth = nullptr;
    m_bGameStarted = false;
    m_pGameStatistic->SetHiScope(m_pGameStatistic->GetScope());
    ui->m_pqlabeHiScope->setText(QString::number(m_pGameStatistic->GetHiScope()));
    if (m_pGameStatistic->IsGameVictory()) {
        ui->m_pqlabelGameResult->setText(QObject::tr("victory!"));
    }
    else {
        ui->m_pqlabelGameResult->setText(QObject::tr("fail!"));
    }
    ui->m_pqlabelSimleAliensKilled->setText(QString::number(m_pGameStatistic->GetSimpleAliensKilled()));
    ui->m_pqlabelSpeedAliensKilled->setText(QString::number(m_pGameStatistic->GetSpeedAliensKilled()));
    ui->m_pqlabelTotalKilled->setText(QString::number(m_pGameStatistic->GetTotalKilled()));
    ui->m_pqlabelYourScope->setText(QString::number(m_pGameStatistic->GetScope()));

    ui->m_pqpbNewGame->setVisible(true);
    ui->m_pqpbNewGame->setFocusPolicy(Qt::NoFocus);
}
//================================================================================================================
void MainWindow::slotNewGame()
{
    ui->m_pqpbNewGame->setVisible(false);
    m_pGameStatistic->Reset();
    SetGame();
}
//================================================================================================================
void MainWindow::SetGame()
{
    const int CELL_SIDE = 40;
    const int QUANTITY_ROWS = 15, QUANTITY_COLUMNS = 15;
    const int WIDTH_GAME_MAP = CELL_SIDE * QUANTITY_COLUMNS;
    const int HEIGHT_GAME_MAP = CELL_SIDE * QUANTITY_ROWS;
    Labyrinth::SetDimension(QUANTITY_COLUMNS, QUANTITY_ROWS);
    m_bGameStarted = true;
    m_pLabyrinth = new Labyrinth(CELL_SIDE, this);
    m_pLabyrinth->setGeometry(0,0,WIDTH_GAME_MAP + 3*CELL_SIDE, HEIGHT_GAME_MAP);
    connect(m_pLabyrinth, SIGNAL(sigGameOver()), this, SLOT(slotGameOver()));
    m_pLabyrinth->show();
    m_pLabyrinth->setFocus();
}
//================================================================================================================
