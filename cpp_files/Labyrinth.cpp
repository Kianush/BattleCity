#include "Labyrinth.h"
#include "LabyrinthCell.h"
#include "AlienPanzers.h"
#include "SpeedAlienPanzer.h"
#include "OurPanzer.h"
#include "PrizesThings.h"
#include "FlagPrize.h"
#include "KillThemAllPrize.h"
#include "FrozePrize.h"
#include "Bullet.h"
#include "BulletExplosion.h"
#include "ExternalWall.h"
#include "FreeSpace.h"
#include "InternalWall.h"
#include "IronInternalWall.h"
#include "GameStatistic.h"
#include "MainDeclarativeView.h"
#include "AudioDelegate.h"
#include "BigExplosion.h"
//===============================================================================================================
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QKeyEvent>
//#include <QSound>
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
                                           QDeclarativeView * pMainDeclarativeView,
                                           const int &iOwnerCodeOfBulletsOfAliens)
{
    GameThings::SetCellSizeOfSide(40);
    GameThings::SetPointerGameStatistic(pGameStatistic);
    GameThings::SetPointerMainDeclarativeView(pMainDeclarativeView);
    AlienPanzer::SetCodeOwnerOfBullets(iOwnerCodeOfBulletsOfAliens);
    AlienPanzer::SetDimensionsOfMainImage(27, 35);
    Bullet::SetDimensionsOfBullet(7,7);
}
//===============================================================================================================
Labyrinth::Labyrinth(const int iSizeOfSideOfCell,
                     AudioDelegate *pAudioDelegate,
                     QWidget *pParent) : QWidget(pParent)
{
    //setFocusPolicy(Qt::StrongFocus);
    m_iDeadTime = 3000;
    m_pAudioDelegate = pAudioDelegate;
    GameThings::SetAudioDelegate(m_pAudioDelegate);
    m_pAudioDelegate->PlayOurStop();
    m_bGameOver = false;
    m_pGameStatistic = GameThings::GetPointerGameStatistic();
    m_iSizeOfSideOfCell = iSizeOfSideOfCell;
    const int QUANTITY_LIVE_HITS = 2;
    OurPanzer::SetLiveCount(QUANTITY_LIVE_HITS);
    CreateCells();
    SetNeighbours();
    BuildExternalWalls();
    BuildInternalWalls();
    CreateOurFlag();
    CreateAliens();
    CreatePrize();
    m_pOurPanzer = nullptr;
    CreateOur();

    m_iGameTick = 40;

    m_iTimerId = startTimer(m_iGameTick);
//    m_pSound_Move = new QSound(":/audio/our_move.wav", this);
//    m_pSound_Stop = new QSound(":/audio/our_stop.wav", this);
//    m_pSound_Move->setLoops(QSound::Infinite);
//    m_pSound_Stop->setLoops(QSound::Infinite);
//    m_pSound_Stop->play();
}
//===============================================================================================================
Labyrinth::~Labyrinth()
{
    m_pAudioDelegate->StopGameAudio();
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
    for (int bullet_explosion_count = 0; bullet_explosion_count < m_qlist_BulletExplosions.size(); ++bullet_explosion_count) {
        BulletExplosion * pBulletExplosion = m_qlist_BulletExplosions[bullet_explosion_count];
        m_qlist_BulletExplosions[bullet_explosion_count] = nullptr;
        delete pBulletExplosion;
    }
    m_qlist_BulletExplosions.clear();
    for (int big_explosion_count = 0; big_explosion_count < m_qlist_BigExplosions.size(); ++big_explosion_count) {
        BigExplosion * pBigExplosion = m_qlist_BigExplosions[big_explosion_count];
        m_qlist_BigExplosions[big_explosion_count] = nullptr;
        delete pBigExplosion;
    }
    m_qlist_BigExplosions.clear();
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
    //delete m_pSound_Move;
    //delete m_pSound_Stop;
}
//===============================================================================================================
void Labyrinth::Draw()
{
    for(int column_count = 0; column_count < m_qvec_LabyrinthCell.size(); ++column_count) {
        foreach (LabyrinthCell * pLabyrinthCell, m_qvec_LabyrinthCell[column_count]) {
            if (nullptr != pLabyrinthCell->GetStaticCellObject()) {
                pLabyrinthCell->GetStaticCellObject()->Draw();
            }
        }
    }
    foreach (Prize * pPrize, m_qlist_Prizes) {
        pPrize->Draw();
    }

    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        pAlienPanzer->Draw();
    }
    foreach (AlienPanzer * pAlienPanzer, m_qlist_ExternalAliens) {
        pAlienPanzer->Draw();
    }
    foreach (Bullet * pBullet, m_qlist_Bullets) {
        pBullet->Draw();
    }
    foreach (BulletExplosion * pBulletExplosion, m_qlist_BulletExplosions) {
        pBulletExplosion->Draw();
    }
    foreach(BigExplosion * pBigExplosion, m_qlist_BigExplosions) {
        pBigExplosion->Draw();
    }

    if (m_pOurPanzer) {
        m_pOurPanzer->Draw();
    }
    if (nullptr != m_pOurFlag) {
        m_pOurFlag->Draw();
    }
}
//===============================================================================================================
void Labyrinth::slotKeyPress(const int &iKey)
{
    if (m_pOurPanzer != nullptr) {
        const int DEFAULT_OUR_VELOSITY = 5;
        if (iKey == Qt::Key_Space) {
            if (!m_pOurPanzer->IsShooting()) {
                m_qlist_Bullets.push_back(m_pOurPanzer->Shoot());
            }
        }
        if (iKey == Qt::Key_Up || iKey == Qt::Key_Down || iKey == Qt::Key_Left || iKey == Qt::Key_Right) {
            m_pOurPanzer->SetVelosity(DEFAULT_OUR_VELOSITY);
            m_pAudioDelegate->PlayOurMove();
//            m_pSound_Stop->stop();
//            m_pSound_Move->play();
        }
        if (iKey == Qt::Key_Up) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Up);
        }
        if(iKey == Qt::Key_Down) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Down);
        }
        if(iKey == Qt::Key_Left) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Left);
        }
        if(iKey == Qt::Key_Right) {
            m_pOurPanzer->SetOrientation(DynamicGameThings::Right);
        }
    }
}
//===============================================================================================================
void Labyrinth::slotKeyRelease(const int &iKey)
{
    if (m_pOurPanzer != nullptr) {
        if (iKey == Qt::Key_Up || iKey == Qt::Key_Down || iKey == Qt::Key_Left || iKey == Qt::Key_Right)
        {
            m_pOurPanzer->SetVelosity(0);
            m_pAudioDelegate->PlayOurStop();
//            m_pSound_Stop->play();
//            m_pSound_Move->stop();
        }
        else if (iKey == Qt::Key_Space) {
                m_pOurPanzer->UnsetShootingSign();
        }
        else {}
    }
    else {}
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
    AlienPanzer::ResetAliensInGame(0);
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
    Prize * pPrize;
    if (rand() % 2 == 0) {
        pPrize = new KillThemAllPrize(7, 6, this);
    }
    else {
        pPrize = new FrozePrize(1, 11, this);
    }
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
    //m_pAudioDelegate->StopGameAudio();
}
//===============================================================================================================
int Labyrinth::DecrementDeadTime(const int &iTick)
{
    //static int iDeadTime = 3000;
    m_iDeadTime -= iTick;
    return m_iDeadTime;
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
    bool bAtLeastOne = false;
    while (it_first!=it_end) {
        (*it_first)->MarkToDelete();
        m_qlist_BigExplosions.push_back((*it_first)->CreateBigExplosion());
        bAtLeastOne = true;
        ++it_first;
    }
    if (bAtLeastOne) {
        //QSound::play(":/audio/explosion.wav");
        m_pAudioDelegate->PlayExplosion();
    }
}
//===============================================================================================================
void Labyrinth::FrozeAliens()
{
    m_bFrozeAliens = true;
    m_iTimeFroze = m_iGameTick * 150;
}
//===============================================================================================================
void Labyrinth::DecrementFrozeTime(const int &iTick)
{
    if (m_bFrozeAliens) {
        m_iTimeFroze -= iTick;
        if (m_iTimeFroze < 0) {
            m_bFrozeAliens = false;
        }
    }
}
//===============================================================================================================
void Labyrinth::BuildExternalWalls()
{

    GameThings * pStaticGameThings = new ExternalWall(0,0);
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

    GameThings * pStaticGameThings;
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
    m_qvec_LabyrinthCell[m_pOurFlag->GetColumn()][m_pOurFlag->GetRow()]->SetDynamicCellObject(m_pOurFlag);
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
void Labyrinth::OursStepInGame()
{
    if (nullptr != m_pOurPanzer) {
        int c = m_pOurPanzer->GetColumn();
        int r = m_pOurPanzer->GetRow();
        m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(m_pOurPanzer);
        if(m_pOurPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r]) ||
           m_pOurPanzer->CanMoveIntoCurrentCell()) {
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
}
//===============================================================================================================
void Labyrinth::AliensStepInGame(const int &iTime)
{
    DecrementFrozeTime(m_iGameTick);
    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        int c = pAlienPanzer->GetColumn();
        int r = pAlienPanzer->GetRow();
        if (c < m_siCellsInColumnQuantity && r < m_siCellsInRowQuantity) {
            m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(pAlienPanzer);
        }
    }
    foreach (AlienPanzer * pAlienPanzer, m_qlist_Aliens) {
        if (!pAlienPanzer->IsDead() && !pAlienPanzer->IsBorning() && !m_bFrozeAliens) {
            int c = pAlienPanzer->GetColumn();
            int r = pAlienPanzer->GetRow();
            if (c < m_siCellsInColumnQuantity && r < m_siCellsInRowQuantity) {
                if(pAlienPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r]) ||
                   pAlienPanzer->CanMoveIntoCurrentCell()) {
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
//                    if (!pAlienPanzer->CanMoveIntoCurrentCell()) {
//                        if (pAlienPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r]->GetLower())) {
//                            pAlienPanzer->SetOrientation(DynamicGameThings::Down);
//                            if (pAlienPanzer->CanMoveToTheNextCell(m_qvec_LabyrinthCell[c][r])) {
//                                bool bCellChange = false;
//                                pAlienPanzer->Move(bCellChange);
//                                if (bCellChange) {
//                                    m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(nullptr);
//                                    int c = pAlienPanzer->GetColumn();
//                                    int r = pAlienPanzer->GetRow();
//                                    m_qvec_LabyrinthCell[c][r]->SetDynamicCellObject(pAlienPanzer);
//                                }
//                            }
//                            else {
//                                pAlienPanzer->DummyRotate();
//                            }
//                        }
//                        else {
//                            pAlienPanzer->DummyRotate();
//                        }
//                    }

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
        else if (pAlienPanzer->IsBorning() && !m_bFrozeAliens) {
            pAlienPanzer->DecreaseBornTime(m_iGameTick);
        }
    }
}
//===============================================================================================================
void Labyrinth::PrizesStepInGame(const int &iTime)
{
    if(iTime > 0 && (iTime % (m_iGameTick*1000) == 0)) {
        CreatePrize();
    }
    foreach (Prize * pPrize, m_qlist_Prizes) {
        if (!pPrize->IsMarkedToDelete()) {
            pPrize->DecrementLiveTime();
            if (!pPrize->IsEffect() && nullptr != m_pOurPanzer) {
                pPrize->OurPanzerHanler(m_pOurPanzer);
            }
            else {
                pPrize->DecrementShowPrizeCostTime();
            }
        }
    }
}
//===============================================================================================================
void Labyrinth::BulletsExplosionStepInGame()
{
    foreach (BulletExplosion * pBulletExplosion, m_qlist_BulletExplosions) {
        pBulletExplosion->DecrementTick();
    }
}
//===============================================================================================================
void Labyrinth::BigExplosionStepInGame()
{
    foreach (BigExplosion * pBigExplosion, m_qlist_BigExplosions) {
        pBigExplosion->DecrementTick();
    }
}
//===============================================================================================================
void Labyrinth::BulletsStepInGame()
{
    foreach (Bullet * pBullet, m_qlist_Bullets) {

        bool bCellChange = false;
        pBullet->Move(bCellChange);
        if (bCellChange) {
            int c = pBullet->GetColumn();
            int r = pBullet->GetRow();
            GameThings * pStaticGameThing = m_qvec_LabyrinthCell[c][r]->GetStaticCellObject();
            pStaticGameThing->BulletHitHandler(pBullet);
            if (pStaticGameThing->IsExplosion()) {
                m_qlist_BigExplosions.push_back(pStaticGameThing->CreateBigExplosion());
                pStaticGameThing->SetExplosion(false);
            }
            DynamicGameThings * pDynamicGameThings = m_qvec_LabyrinthCell[c][r]->GetDynamicGameThings();
            if (nullptr != pDynamicGameThings) {
                pDynamicGameThings->BulletHitHandler(pBullet);
                if(pDynamicGameThings->IsExplosion()) {
                    m_qlist_BigExplosions.push_back(pDynamicGameThings->CreateBigExplosion());
                    pDynamicGameThings->SetExplosion(false);
                }
            }
            if (nullptr != m_pOurFlag) {
                if (m_pOurFlag->GetColumn() == c && m_pOurFlag->GetRow() == r) {
                    m_pOurFlag->BulletHitHandler(pBullet);
                    if (m_pOurFlag->IsExplosion()) {
                        m_qlist_BigExplosions.push_back(m_pOurFlag->CreateBigExplosion());
                        m_pOurFlag->SetExplosion(false);
                    }
                }
            }
        }
        if (pBullet->IsMarkedToDelete()) {
            BulletExplosion * pBulletExplosion = pBullet->GetExplosion();
            m_qlist_BulletExplosions.push_back(pBulletExplosion);
        }
    }
}
//===============================================================================================================
void Labyrinth::CleanOursStepInGame()
{
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
            m_qvec_LabyrinthCell[m_pOurFlag->GetColumn()][m_pOurFlag->GetRow()]->RemoveDynamicGameThings(m_pOurFlag);
            delete m_pOurFlag;
            m_pOurFlag = nullptr;
        }
    }
}
//===============================================================================================================
void Labyrinth::CleanAliensStepInGame()
{
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
           AlienPanzer::DecrementQuantityAliens();
           delete pAlienPanzer;
           m_qlist_Aliens.erase(it_first_alien);
           it_first_alien = m_qlist_Aliens.begin();
           it_end_alien = m_qlist_Aliens.end();
           continue;
        }
        it_first_alien++;
    }
}
//===============================================================================================================
void Labyrinth::CleanPrizesStepInGame()
{
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
}
//===============================================================================================================
void Labyrinth::CleanBulletsStepInGame()
{
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
}
//===============================================================================================================
void Labyrinth::CleanBulletsExplosionStepInGame()
{
    auto it_first_bullet_explosion = m_qlist_BulletExplosions.begin();
    auto it_end_bullet_explosion = m_qlist_BulletExplosions.end();
    while (it_first_bullet_explosion != it_end_bullet_explosion) {
        if ((*it_first_bullet_explosion)->GetTick() < 0) {
            BulletExplosion * pBulletExplosion = (*it_first_bullet_explosion);
            delete pBulletExplosion;
            m_qlist_BulletExplosions.erase(it_first_bullet_explosion);
            it_first_bullet_explosion = m_qlist_BulletExplosions.begin();
            it_end_bullet_explosion = m_qlist_BulletExplosions.end();
            continue;
        }
        it_first_bullet_explosion++;
    }
}
//===============================================================================================================
void Labyrinth::CleanBigExplosionStepInGame()
{
    auto it_first_big_explosion = m_qlist_BigExplosions.begin();
    auto it_end_big_explosion = m_qlist_BigExplosions.end();
    while (it_first_big_explosion != it_end_big_explosion) {
        if ((*it_first_big_explosion)->GetTick() < 0) {
            BigExplosion * pBigExplosion = (*it_first_big_explosion);
            delete pBigExplosion;
            m_qlist_BigExplosions.erase(it_first_big_explosion);
            it_first_big_explosion = m_qlist_BigExplosions.begin();
            it_end_big_explosion = m_qlist_BigExplosions.end();
            continue;
        }
        it_first_big_explosion++;
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
    OursStepInGame();
    PlacingAlienInGame(iTime);

    iTime += m_iGameTick;

    AliensStepInGame(iTime);
    PrizesStepInGame(iTime);
    BulletsExplosionStepInGame();
    BigExplosionStepInGame();
    BulletsStepInGame();

    CleanPrizesStepInGame();
    CleanBulletsStepInGame();
    CleanBulletsExplosionStepInGame();
    CleanBigExplosionStepInGame();
    CleanAliensStepInGame();
    CleanOursStepInGame();
    Draw();
    QObject::timerEvent(pTimerEvent);
}
//===============================================================================================================
