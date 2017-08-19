#include "Labyrinth.h"
#include "LabyrinthCell.h"
#include "AlienPanzers.h"
#include "SpeedAlienPanzer.h"
#include "OurPanzer.h"
#include "PrizesThings.h"
#include "FlagPrize.h"
#include "KillThemAllPrize.h"
#include "Bullet.h"
#include "StaticGameThings.h"
#include "ExternalWall.h"
#include "FreeSpace.h"
#include "InternalWall.h"
#include "IronInternalWall.h"
#include "GameStatistic.h"
//===============================================================================================================
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QKeyEvent>
//===============================================================================================================
int Labyrinth::m_siCellsInColumnQuantity;
int Labyrinth::m_siCellsInRowQuantity;
//===============================================================================================================
void Labyrinth::SetDimension(const int &iQuantityRows, const int &iQuantityColumns)
{
    m_siCellsInColumnQuantity = iQuantityColumns;
    m_siCellsInRowQuantity = iQuantityRows;
}
//===============================================================================================================
void Labyrinth::SetInternalStaticVariables(GameStatistic * pGameStatistic,
                                           const int &iOwnerCodeOfBulletsOfAliens)
{
    GameThings::SetCellSizeOfSide(40);
    GameThings::SetPointerGameStatistic(pGameStatistic);
    AlienPanzer::SetRotatedSimpleAlienPathes();
    AlienPanzer::SetCodeOwnerOfBullets(iOwnerCodeOfBulletsOfAliens);
    KillThemAllPrize::SetKillThemAllPrizePath();
    FlagPrize::SetFlagPrizePath();

}
//===============================================================================================================
Labyrinth::Labyrinth(const int iSizeOfSideOfCell, QWidget *pParent) : QWidget(pParent)
{
    setFocusPolicy(Qt::StrongFocus);
    m_bGameOver = false;
    m_pGameStatistic = GameThings::GetPointerGameStatistic();
    m_iSizeOfSideOfCell = iSizeOfSideOfCell;
    const int QUANTITY_LIVE_HITS = 3;
    OurPanzer::SetLiveCount(QUANTITY_LIVE_HITS);
    CreateCells();
    SetNeighbours();
    BuildExternalWalls();
    BuildInternalWalls();
    CreateOurFlag();
    CreateAliens();
    CreatePrize();
    CreateOur();

    m_iGameTick = 40;

    m_iTimerId = startTimer(m_iGameTick);
}
//===============================================================================================================
Labyrinth::~Labyrinth()
{
    Clean();
}
//===============================================================================================================
void Labyrinth::Clean()
{
    for (int column_count = 0; column_count < m_siCellsInColumnQuantity; ++column_count) {
        for(int row_count = 0; row_count < m_siCellsInRowQuantity; ++row_count) {
            LabyrinthCell * pLabyrinthCell = m_qvec_LabyrinthCell[column_count][row_count];
            m_qvec_LabyrinthCell[column_count][row_count] = nullptr;
            delete pLabyrinthCell;
        }
    }
    m_qvec_LabyrinthCell.clear();
    for(int alien_count = 0; alien_count < m_qlist_Aliens.size(); ++alien_count) {
        AlienPanzer * pAlienPanzer = m_qlist_Aliens[alien_count];
        m_qlist_Aliens[alien_count] = nullptr;
        delete pAlienPanzer;
    }
    m_qlist_Aliens.clear();
    for(int alien_count = 0; alien_count < m_qlist_ExternalAliens.size(); ++alien_count) {
        AlienPanzer * pAlienPanzer = m_qlist_ExternalAliens[alien_count];
        m_qlist_ExternalAliens[alien_count] = nullptr;
        delete pAlienPanzer;
    }
    m_qlist_ExternalAliens.clear();
    for (int bullet_count = 0; bullet_count< m_qlist_Bullets.size(); ++bullet_count) {
        Bullet * pBullet = m_qlist_Bullets[bullet_count];
        m_qlist_Bullets[bullet_count] = nullptr;
        delete pBullet;
    }
    m_qlist_Bullets.clear();
    if (nullptr != m_pOurPanzer) {
        delete m_pOurPanzer;
        m_pOurPanzer = nullptr;
    }
    for (int prize_count = 0; prize_count < m_qlist_Prizes.size(); ++prize_count) {
        Prize * pPrize = m_qlist_Prizes[prize_count];
        delete pPrize;
        m_qlist_Prizes[prize_count] = nullptr;
    }
    m_qlist_Prizes.clear();
    if (nullptr != m_pOurFlag) {
        delete m_pOurFlag;
    }
}
//===============================================================================================================
void Labyrinth::draw(QPainter *pPainter)
{
    for(int column_count = 0; column_count < m_qvec_LabyrinthCell.size(); ++column_count) {
        foreach (LabyrinthCell * pLabyrinthCell, m_qvec_LabyrinthCell[column_count]) {
            if (nullptr != pLabyrinthCell->GetStaticCellObject()) {
                pLabyrinthCell->GetStaticCellObject()->Draw(pPainter);
            }
        }
    }
    foreach (Prize * pPrize, m_qlist_Prizes) {
        pPrize->Draw(pPainter);
    }

    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        pAlienPanzer->Draw(pPainter);
    }
    foreach (AlienPanzer * pAlienPanzer, m_qlist_ExternalAliens) {
        pAlienPanzer->Draw(pPainter);
    }
    foreach (Bullet * pBullet, m_qlist_Bullets) {
        pBullet->Draw(pPainter);
    }
    if (m_pOurPanzer) {
        m_pOurPanzer->Draw(pPainter);
    }
    if (nullptr != m_pOurFlag) {
        m_pOurFlag->Draw(pPainter);
    }
}
//===============================================================================================================
void Labyrinth::paintEvent(QPaintEvent * pPaintEvent)
{
    Q_UNUSED(pPaintEvent);
    QPainter thePainter(this);
    if(!thePainter.isActive()) return;
    thePainter.setRenderHint(QPainter::Antialiasing);
    draw(&thePainter);
}
//===============================================================================================================
void Labyrinth::keyPressEvent(QKeyEvent * pKeyEvent)
{
    if (m_pOurPanzer != nullptr) {
        const int DEFAULT_OUR_VELOSITY = 5;
        if (pKeyEvent->key() == Qt::Key_Space) {
            if (!m_pOurPanzer->IsShooting() && !pKeyEvent->isAutoRepeat()) {
                m_qlist_Bullets.push_back(m_pOurPanzer->Shoot());
            }
        }
        if (pKeyEvent->key() == Qt::Key_Up) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Up);
            m_pOurPanzer->SetVelosity(DEFAULT_OUR_VELOSITY);
        }
        if(pKeyEvent->key() == Qt::Key_Down) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Down);
            m_pOurPanzer->SetVelosity(DEFAULT_OUR_VELOSITY);
        }
        if(pKeyEvent->key() == Qt::Key_Left) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Left);
            m_pOurPanzer->SetVelosity(DEFAULT_OUR_VELOSITY);
        }
        if(pKeyEvent->key() == Qt::Key_Right) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Right);
            m_pOurPanzer->SetVelosity(DEFAULT_OUR_VELOSITY);
        }
    }
    QWidget::keyPressEvent(pKeyEvent);
}
//===============================================================================================================
void Labyrinth::keyReleaseEvent(QKeyEvent * pKeyEvent)
{
    if (m_pOurPanzer != nullptr) {
        if (pKeyEvent->key() == Qt::Key_Up ||
            pKeyEvent->key() == Qt::Key_Down ||
            pKeyEvent->key() == Qt::Key_Left ||
            pKeyEvent->key() == Qt::Key_Right)
        {
            m_pOurPanzer->SetVelosity(0);
        }
        else if (pKeyEvent->key() == Qt::Key_Space) {
            if (!pKeyEvent->isAutoRepeat()) {
                m_pOurPanzer->UnsetShootingSign();
            }
        }
        else {}
    }
    else {}
    QWidget::keyReleaseEvent(pKeyEvent);
}
//===============================================================================================================
void Labyrinth::CreateCells()
{
    QVector<LabyrinthCell *> qvecRow;
    qvecRow.reserve(m_siCellsInRowQuantity);
    for (int column_count = 0; column_count < m_siCellsInColumnQuantity; ++column_count) {
        for(int row_count = 0; row_count < m_siCellsInRowQuantity; ++row_count) {
            LabyrinthCell * pLabyrinthCell = new LabyrinthCell();
            qvecRow.push_back(pLabyrinthCell);
        }
        m_qvec_LabyrinthCell.push_back(qvecRow);
        qvecRow.clear();
    }
}
//===============================================================================================================
void Labyrinth::CreateAliens()
{
    AlienPanzer::SetQuantitySimpleAliens(20);
    AlienPanzer ** pArrayAliens = new AlienPanzer*[AlienPanzer::GetQuantitySimpleAliens()];
    for(int alien_count = 0; alien_count < AlienPanzer::GetQuantitySimpleAliens(); alien_count = alien_count + 2) {
        if (alien_count != 0) {
            pArrayAliens[alien_count] = new AlienPanzer(m_siCellsInColumnQuantity + 1, alien_count/2);
            pArrayAliens[alien_count+1] = new AlienPanzer(m_siCellsInColumnQuantity + 2, alien_count/2);
        }
        else {
            pArrayAliens[alien_count] = new SpeedAlienPanzer(m_siCellsInColumnQuantity + 1, alien_count/2);
            pArrayAliens[alien_count+1] = new SpeedAlienPanzer(m_siCellsInColumnQuantity + 2, alien_count/2);
        }
        pArrayAliens[alien_count]->SetVelosity(0);
        pArrayAliens[alien_count+1]->SetVelosity(0);
        m_qlist_ExternalAliens.push_front(pArrayAliens[alien_count]);
        m_qlist_ExternalAliens.push_front(pArrayAliens[alien_count+1]);
    }
    delete [] pArrayAliens;
}
//===============================================================================================================
void Labyrinth::PlacingAlienInGame(const int &iTime)
{
    if (iTime % 3000 == 0) {
        static int iPlacingCount = 0;
        auto it_first_external_alien = m_qlist_ExternalAliens.begin();
        auto it_end_external_alien = m_qlist_ExternalAliens.end();
        if (it_first_external_alien != it_end_external_alien) {
            AlienPanzer * pAlien = (*it_first_external_alien);
            m_qlist_ExternalAliens.pop_front();
            if (iPlacingCount % 3 == 0) {
                pAlien->SetColumn(6);
                pAlien->SetRow(1);
            }
            else if (iPlacingCount % 3 == 1) {
                pAlien->SetColumn(1);
                pAlien->SetRow(1);
            }
            else {
                pAlien->SetColumn(13);
                pAlien->SetRow(1);
            }
            pAlien->SetTypicalVelosity();
            pAlien->SetBorning();
            m_qlist_Aliens.push_back(pAlien);
            iPlacingCount++;
        }
    }
}
//===============================================================================================================
bool Labyrinth::CreateOur()
{
    bool bToReturn = false;
    if (OurPanzer::GetLiveCount() > 0) {
        m_pOurPanzer = new OurPanzer(5,13);
        bToReturn = true;
    }
    else {
        bToReturn = false;
        m_pGameStatistic->SetGameResult(false);
        DoGameOver();
    }
    return bToReturn;
}
//===============================================================================================================
void Labyrinth::CreatePrize()
{
    Prize * pPrize = new KillThemAllPrize(7, 6, this);
    pPrize->SetPrizeCost(500);
    m_qlist_Prizes.push_back(pPrize);
}
//===============================================================================================================
void Labyrinth::DoGameOver()
{
    m_bGameOver = true;
    m_pGameStatistic->SetGameResult(true);
    if (nullptr != m_pOurFlag) {
        if (OurPanzer::GetLiveCount() <= 0 || m_pOurFlag->IsMarkedToDelete())
        {
            m_pGameStatistic->SetGameResult(false);
        }
    }
    else {
        m_pGameStatistic->SetGameResult(false);
    }
}
//===============================================================================================================
int Labyrinth::DecrementDeadTime(const int &iTick)
{
    static int iDeadTime = 3000;
    iDeadTime -= iTick;
    return iDeadTime;
}
//===============================================================================================================
void Labyrinth::ExitLevel()
{
    killTimer(m_iTimerId);
    emit sigGameOver();
}

//===============================================================================================================
void Labyrinth::KillAllAliens()
{
    auto it_first = m_qlist_Aliens.begin();
    auto it_end = m_qlist_Aliens.end();
    while (it_first!=it_end) {
        (*it_first)->MarkToDelete();
        ++it_first;
    }
}
//===============================================================================================================
void Labyrinth::BuildExternalWalls()
{

    StaticGameThings * pStaticGameThings = new ExternalWall(0,0);
    m_qvec_LabyrinthCell[0][0]->SetStaticCellObject(pStaticGameThings);
    pStaticGameThings = new ExternalWall(m_siCellsInColumnQuantity - 1,0);
    m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][0]->SetStaticCellObject(pStaticGameThings);
    pStaticGameThings = new ExternalWall(0,m_siCellsInRowQuantity - 1);
    m_qvec_LabyrinthCell[0][m_siCellsInRowQuantity - 1]->SetStaticCellObject(pStaticGameThings);
    pStaticGameThings = new ExternalWall(m_siCellsInColumnQuantity - 1, m_siCellsInRowQuantity - 1);
    m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][m_siCellsInRowQuantity - 1]->SetStaticCellObject(pStaticGameThings);

    for(int column_count = 1; column_count < m_siCellsInColumnQuantity - 1; ++column_count) {
        pStaticGameThings = new ExternalWall(column_count, 0);
        m_qvec_LabyrinthCell[column_count][0]->SetStaticCellObject(pStaticGameThings);
        pStaticGameThings = new ExternalWall(column_count, m_siCellsInRowQuantity - 1);
        m_qvec_LabyrinthCell[column_count][m_siCellsInRowQuantity - 1]->SetStaticCellObject(pStaticGameThings);
    }

    for (int row_count = 1; row_count < m_siCellsInRowQuantity - 1; ++row_count) {
        pStaticGameThings = new ExternalWall(0, row_count);
        m_qvec_LabyrinthCell[0][row_count]->SetStaticCellObject(pStaticGameThings);
        pStaticGameThings = new ExternalWall(m_siCellsInColumnQuantity - 1, row_count);
        m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][row_count]->SetStaticCellObject(pStaticGameThings);
    }
}
//===============================================================================================================
bool Labyrinth::CellLessThan(const QPoint &p1, const QPoint &p2)
{
    return (p1.y()*m_siCellsInColumnQuantity+p1.x() < p2.y()*m_siCellsInColumnQuantity+p2.x());
}
//===============================================================================================================
void Labyrinth::BuildInternalWalls()
{
    QVector<QPoint> qvecInternalStoneWallsCellIndex;
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,4));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,5));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,10));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,11));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(2,12));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,4));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,5));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,10));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,11));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,12));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,4));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,5));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,10));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,11));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,12));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,4));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,5));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,10));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,11));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(12,12));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,4));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,8));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,10));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,2));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,3));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,4));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,8));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,9));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,10));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(3,7));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(4,7));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(10,7));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(11,7));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,6));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,6));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(7,9));

    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,13));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(6,12));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(7,12));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,12));
    qvecInternalStoneWallsCellIndex.push_back(QPoint(8,13));

    qSort(qvecInternalStoneWallsCellIndex.begin(), qvecInternalStoneWallsCellIndex.end(), CellLessThan);

    QVector<QPoint> qvecInternalIronWallsCellIndex;
    qvecInternalIronWallsCellIndex.push_back(QPoint(1,7));
    qvecInternalIronWallsCellIndex.push_back(QPoint(13,7));
    qvecInternalIronWallsCellIndex.push_back(QPoint(7,3));

    qSort(qvecInternalIronWallsCellIndex.begin(), qvecInternalIronWallsCellIndex.end(), CellLessThan);

    QVector<QPoint> qvecFreeSpace;
    for(int column_count = 1; column_count < m_siCellsInColumnQuantity - 1; ++column_count) {
        for(int row_count = 1; row_count < m_siCellsInRowQuantity - 1; ++row_count) {
            if ((qFind(qvecInternalStoneWallsCellIndex.begin(),
                      qvecInternalStoneWallsCellIndex.end(), QPoint(column_count, row_count)) ==
                 qvecInternalStoneWallsCellIndex.end()) &&
                (qFind(qvecInternalIronWallsCellIndex.begin(),
                       qvecInternalIronWallsCellIndex.end(), QPoint(column_count, row_count)) ==
                       qvecInternalIronWallsCellIndex.end())) {

                qvecFreeSpace.push_back(QPoint(column_count, row_count));
            }
        }
    }
    qSort(qvecFreeSpace.begin(), qvecFreeSpace.end(), CellLessThan);

    StaticGameThings * pStaticGameThings;
    int iC, iR;
    for(int cell = 0; cell < qvecInternalStoneWallsCellIndex.size(); ++cell) {
        iC = qvecInternalStoneWallsCellIndex[cell].x();
        iR = qvecInternalStoneWallsCellIndex[cell].y();
        pStaticGameThings = new InternalWall(iC, iR);
        m_qvec_LabyrinthCell[iC][iR]->SetStaticCellObject(pStaticGameThings);
    }
    for(int cell = 0; cell < qvecInternalIronWallsCellIndex.size(); ++cell) {
        iC = qvecInternalIronWallsCellIndex[cell].x();
        iR = qvecInternalIronWallsCellIndex[cell].y();
        pStaticGameThings = new IronInternalWall(iC, iR);
        m_qvec_LabyrinthCell[iC][iR]->SetStaticCellObject(pStaticGameThings);
    }
    for(int cell = 0; cell < qvecFreeSpace.size(); ++cell) {
        iC = qvecFreeSpace[cell].x();
        iR = qvecFreeSpace[cell].y();
        pStaticGameThings = new FreeSpace(iC, iR);
        m_qvec_LabyrinthCell[iC][iR]->SetStaticCellObject(pStaticGameThings);
    }
}
//===============================================================================================================
void Labyrinth::CreateOurFlag()
{
    m_pOurFlag = new FlagPrize(7,13, this);
}
//===============================================================================================================
void Labyrinth::SetNeighbours()
{
    m_qvec_LabyrinthCell[0][0]->SetNeighbours(nullptr, m_qvec_LabyrinthCell[1][0],
                                              nullptr, m_qvec_LabyrinthCell[0][1]);
    m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][0]->SetNeighbours(m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 2][0],
                                                                         nullptr, nullptr, m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][1]);
    m_qvec_LabyrinthCell[0][m_siCellsInRowQuantity - 1]->SetNeighbours(nullptr, m_qvec_LabyrinthCell[1][m_siCellsInRowQuantity - 1],
                                                                         m_qvec_LabyrinthCell[0][m_siCellsInRowQuantity - 2], nullptr);
    m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][m_siCellsInRowQuantity - 1]->SetNeighbours(m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 2][m_siCellsInRowQuantity - 1], nullptr,
                                                                                                 m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][m_siCellsInRowQuantity - 2], nullptr);

    for(int column_count = 1; column_count < m_siCellsInColumnQuantity - 1; ++column_count) {
        m_qvec_LabyrinthCell[column_count][0]->SetNeighbours(m_qvec_LabyrinthCell[column_count-1][0],
                                                             m_qvec_LabyrinthCell[column_count+1][0],
                                                             nullptr,
                                                             m_qvec_LabyrinthCell[column_count][1]);
        m_qvec_LabyrinthCell[column_count][m_siCellsInRowQuantity - 1]->SetNeighbours(m_qvec_LabyrinthCell[column_count-1][m_siCellsInRowQuantity - 1],
                                                                                     m_qvec_LabyrinthCell[column_count+1][m_siCellsInRowQuantity - 1],
                                                                                     m_qvec_LabyrinthCell[column_count][m_siCellsInRowQuantity - 2],
                                                                                     nullptr);
    }
    for (int row_count = 1; row_count < m_siCellsInRowQuantity - 1; ++row_count) {
        m_qvec_LabyrinthCell[0][row_count]->SetNeighbours(nullptr,
                                                          m_qvec_LabyrinthCell[1][row_count],
                                                          m_qvec_LabyrinthCell[0][row_count-1],
                                                          m_qvec_LabyrinthCell[0][row_count+1]);
        m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][row_count]->SetNeighbours(m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 2][row_count],
                                                                                     nullptr,
                                                                                     m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][row_count-1],
                                                                                     m_qvec_LabyrinthCell[m_siCellsInColumnQuantity - 1][row_count+1]);
    }
    for(int column_count = 1; column_count < m_siCellsInColumnQuantity - 1; ++column_count) {
        for(int row_count = 1; row_count < m_siCellsInRowQuantity - 1; ++row_count) {
            m_qvec_LabyrinthCell[column_count][row_count]->SetNeighbours(m_qvec_LabyrinthCell[column_count - 1][row_count],
                                                                         m_qvec_LabyrinthCell[column_count + 1][row_count],
                                                                         m_qvec_LabyrinthCell[column_count][row_count - 1],
                                                                         m_qvec_LabyrinthCell[column_count][row_count + 1]);
        }
    }
}
//===============================================================================================================
void Labyrinth::timerEvent(QTimerEvent * pTimerEvent)
{
    static int iTime = 0;
    if (m_bGameOver) {
        if (DecrementDeadTime(m_iGameTick) < 0) {
            ExitLevel();
            return;
        }
    }
    if (AlienPanzer::GetQuantitySimpleAliens() == 0) {
        DoGameOver();
    }
    if (nullptr == m_pOurPanzer) {
        if(!CreateOur()) {}
    }

    if (nullptr != m_pOurPanzer) {
        int c = m_pOurPanzer->GetColumn();
        int r = m_pOurPanzer->GetRow();
        m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(m_pOurPanzer);
        if(m_pOurPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r])) {
            bool bCellChange = false;
            m_pOurPanzer->Move(bCellChange);
            if (bCellChange) {
                m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(nullptr);
                c = m_pOurPanzer->GetColumn();
                r = m_pOurPanzer->GetRow();
                m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(m_pOurPanzer);
            }

        }
    }
    PlacingAlienInGame(iTime);
    iTime += m_iGameTick;

    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        int c = pAlienPanzer->GetColumn();
        int r = pAlienPanzer->GetRow();
        if (c < m_siCellsInColumnQuantity && r < m_siCellsInRowQuantity) {
            m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(pAlienPanzer);
        }
    }

    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        if (!pAlienPanzer->IsDead() && !pAlienPanzer->IsBorning()) {
            int c = pAlienPanzer->GetColumn();
            int r = pAlienPanzer->GetRow();
            if (c < m_siCellsInColumnQuantity && r < m_siCellsInRowQuantity) {
                if(pAlienPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r])) {
                    bool bCellChange = false;
                    pAlienPanzer->Move(bCellChange);
                    if (bCellChange) {
                        m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(nullptr);
                        int c = pAlienPanzer->GetColumn();
                        int r = pAlienPanzer->GetRow();
                        m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(pAlienPanzer);
                    }
                }
                else {
                    pAlienPanzer->DummyRotate();
                }
                if (iTime % 1000 == 0) {
                    m_qlist_Bullets.push_back(pAlienPanzer->Shoot());
                }
            }

        }
        else if (pAlienPanzer->IsDead()){
            pAlienPanzer->DecrementShowCostTime();
        }
        else if (pAlienPanzer->IsBorning()) {
            pAlienPanzer->DecreaseBornTime(m_iGameTick);
        }
    }
    foreach (Prize * pPrize, m_qlist_Prizes) {
        if (!pPrize->IsMarkedToDelete()) {
            pPrize->DecrementLiveTime();
            if (!pPrize->IsEffect()) {
                pPrize->OurPanzerHanler(m_pOurPanzer);
            }
            else {
                pPrize->DecrementShowPrizeCostTime();
            }
        }
    }
    foreach (Bullet * pBullet, m_qlist_Bullets) {

        bool bCellChange = false;
        pBullet->Move(bCellChange);
        if (bCellChange) {
            int c = pBullet->GetColumn();
            int r = pBullet->GetRow();
            m_qvec_LabyrinthCell[c][r]->GetStaticCellObject()->BulletHitHandler(pBullet);
            if (nullptr != m_qvec_LabyrinthCell[c][r]->GetDynamicGameThings()) {
                m_qvec_LabyrinthCell[c][r]->GetDynamicGameThings()->BulletHitHandler(pBullet);
            }
            if (nullptr != m_pOurFlag) {
                if (m_pOurFlag->GetColumn() == c && m_pOurFlag->GetRow() == r) {
                    m_pOurFlag->BulletHitHandler(pBullet);
                }
            }
        }
    }
    auto it_first_prize = m_qlist_Prizes.begin();
    auto it_end_prize = m_qlist_Prizes.end();
    while(it_first_prize != it_end_prize) {
        if ((*it_first_prize)->IsMarkedToDelete()) {
            Prize * pPrize = (*it_first_prize);
            delete pPrize;
            m_qlist_Prizes.erase(it_first_prize);
            it_first_prize = m_qlist_Prizes.begin();
            it_end_prize = m_qlist_Prizes.end();
            continue;
        }
        it_first_prize++;
    }
    auto it_first_bullet = m_qlist_Bullets.begin();
    auto it_end_bullet = m_qlist_Bullets.end();
    while (it_first_bullet != it_end_bullet) {
        if ((*it_first_bullet)->IsMarkedToDelete()) {
            Bullet * pBullet = (*it_first_bullet);
            delete pBullet;
            m_qlist_Bullets.erase(it_first_bullet);
            it_first_bullet = m_qlist_Bullets.begin();
            it_end_bullet = m_qlist_Bullets.end();
            continue;
        }
        it_first_bullet++;
    }
    auto it_first_alien = m_qlist_Aliens.begin();
    auto it_end_alien = m_qlist_Aliens.end();
    while (it_first_alien != it_end_alien) {
        if ((*it_first_alien)->IsMarkedToDelete()) {
           AlienPanzer * pAlienPanzer = (*it_first_alien);
           for(int c = pAlienPanzer->GetColumn() - 1; c <= pAlienPanzer->GetColumn() + 1; ++c) {
               for(int r = pAlienPanzer->GetRow() - 1; r <= pAlienPanzer->GetRow() + 1; ++r) {
                   m_qvec_LabyrinthCell[c][r]->RemoveDynamicGameThings(pAlienPanzer);
               }
           }
           delete pAlienPanzer;
           m_qlist_Aliens.erase(it_first_alien);
           it_first_alien = m_qlist_Aliens.begin();
           it_end_alien = m_qlist_Aliens.end();
        }
        it_first_alien++;
    }
    if ((nullptr != m_pOurPanzer) && m_pOurPanzer->IsMarkedToDelete()) {
        for(int c = m_pOurPanzer->GetColumn() - 1; c <= m_pOurPanzer->GetColumn() + 1; ++c) {
            for(int r = m_pOurPanzer->GetRow() - 1; r <= m_pOurPanzer->GetRow() + 1; ++r) {
                m_qvec_LabyrinthCell[c][r]->RemoveDynamicGameThings(m_pOurPanzer);
            }
        }
        delete m_pOurPanzer;
        m_pOurPanzer = nullptr;
    }
    if (nullptr != m_pOurFlag) {
        if (m_pOurFlag->IsMarkedToDelete()) {
            delete m_pOurFlag;
            m_pOurFlag = nullptr;
        }
    }
    repaint();
    QWidget::timerEvent(pTimerEvent);
}
//===============================================================================================================
