#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Labyrinth.h"
#include "GameStatistic.h"
#include "MainDeclarativeView.h"
#include "AudioDelegate.h"
#include "AudioThread.h"
//================================================================================================================
#include <QKeyEvent>
#include <QString>
#include <QDebug>
//================================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_pqdvUi = new MainDeclarativeView;
    m_pAudioDelegate = new AudioDelegate(this);
    m_pGameAudioThread = new GameAudioThread(m_pAudioDelegate, this);
    m_pGameAudioThread->start();
    m_pqdvUi->setSource(QUrl("qrc:/qml/main.qml"));
    setCentralWidget(m_pqdvUi);
    setMaximumHeight(m_pqdvUi->height());
    m_pqdvUi->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    m_pRoot = m_pqdvUi->rootObject();
    m_pqdvUi->rootContext()->setContextProperty("window", this);
    m_pGameStatistic = new GameStatistic();
    const int  CODE_OWNER_OF_BULLETS_OF_ALIENS = 13;
    Labyrinth::SetInternalStaticVariables(m_pGameStatistic,
                                          m_pqdvUi,
                                          CODE_OWNER_OF_BULLETS_OF_ALIENS);
    SetGame();
}
//================================================================================================================
MainWindow::~MainWindow()
{
    if (nullptr != m_pLabyrinth) {
        delete m_pLabyrinth;
    }
    if (nullptr != m_pGameStatistic) {
        delete m_pGameStatistic;
    }
    if (nullptr != m_pqdvUi) {
        delete m_pqdvUi;
    }
    if (nullptr != m_pAudioDelegate) {
        delete m_pAudioDelegate;
    }
    if (nullptr != m_pGameAudioThread) {
        m_pGameAudioThread->exit();
        delete m_pGameAudioThread;
    }
}
//================================================================================================================
void MainWindow::slotGameOver()
{
    delete m_pLabyrinth;
    m_pLabyrinth = nullptr;
    m_bGameStarted = false;
    m_pGameStatistic->SetHiScope(m_pGameStatistic->GetScope());
    QString qmlObjectName = "game_over";
    QObject * pQmlImage = m_pqdvUi->rootObject()->findChild<QObject*>(qmlObjectName);
    if (m_pGameStatistic->IsGameVictory()) {
        pQmlImage->setProperty("result",QObject::tr("victory!"));
    }
    else {
        pQmlImage->setProperty("result",QObject::tr("fail!"));
    }
    pQmlImage->setProperty("hi_scope", m_pGameStatistic->GetHiScope());
    pQmlImage->setProperty("scope", m_pGameStatistic->GetScope());
    pQmlImage->setProperty("simple_aliens_killed", m_pGameStatistic->GetSimpleAliensKilled());
    pQmlImage->setProperty("speed_aliens_killed", m_pGameStatistic->GetSpeedAliensKilled());
    pQmlImage->setProperty("visible", true);
    m_pGameStatistic->Reset();
}
//================================================================================================================
void MainWindow::slotNewGame()
{
    //ui->m_pqpbNewGame->setVisible(false);
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
    m_pLabyrinth = new Labyrinth(CELL_SIDE, m_pAudioDelegate, this);
    m_pLabyrinth->setGeometry(0,0,WIDTH_GAME_MAP + 3*CELL_SIDE, HEIGHT_GAME_MAP);
    m_pLabyrinth->setVisible(false);
    connect(m_pLabyrinth, SIGNAL(sigGameOver()), this, SLOT(slotGameOver()));
    MainDeclarativeView * pMainDeclarativeView = dynamic_cast<MainDeclarativeView*>(m_pqdvUi);
    QString qmlObjectName = "game_over";
    QObject * pQmlImage = pMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
    if (nullptr != pQmlImage) {
        pQmlImage->setProperty("visible", false);
    }
    if (nullptr != pMainDeclarativeView) {
        connect(pMainDeclarativeView, SIGNAL(sigKeyPress(int)), m_pLabyrinth, SLOT(slotKeyPress(int)));
        connect(pMainDeclarativeView, SIGNAL(sigKeyRelease(int)), m_pLabyrinth, SLOT(slotKeyRelease(int)));
    }
}
//================================================================================================================
void MainWindow::NewGameButtonQmlClick()
{
    slotGameOver();
    SetGame();
}
//================================================================================================================
