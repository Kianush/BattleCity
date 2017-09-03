#ifndef LABIRINTH_H
#define LABIRINTH_H
//=================================================================================================================
#include <QWidget>
#include <QVector>
#include <QList>
//=================================================================================================================
class LabyrinthCell;
class GameThings;
class AlienPanzer;
class OurPanzer;
class Prize;
class Bullet;
class FlagPrize;
class GameStatistic;
class QDeclarativeView;
class BulletExplosion;
class BigExplosion;
class AudioDelegate;
//=================================================================================================================
class Labyrinth : public QWidget
{
Q_OBJECT
public:
    Labyrinth(const int iSizeOfSideOfCell,
              AudioDelegate * pAudioDelegate,
              QWidget * pParent = nullptr);
    virtual ~Labyrinth();

    void KillAllAliens();
    void FrozeAliens();
    static void SetDimension(const int &iQuantityRows, const int &iQuantityColumns);
    static void SetInternalStaticVariables(GameStatistic *pGameStatistic,
                                           QDeclarativeView *pMainDeclarativeView,
                                           const int &iOwnerCodeOfBulletsOfAliens);
    void DoGameOver();
public slots:
    void slotKeyPress(const int &iKey);
    void slotKeyRelease(const int &iKey);
signals:
    void sigGameOver();
protected:
    virtual void timerEvent(QTimerEvent * pTimerEvent);
private:
    void Draw();
    void BuildExternalWalls();
    void BuildInternalWalls();
    void SetNeighbours();
    void CreateCells();
    void CreateAliens();
    void PlacingAlienInGame(const int &iTime);
    bool CreateOur();
    void CreateOurFlag();
    void CreatePrize();
    int DecrementDeadTime(const int &iTick);
    void DecrementFrozeTime(const int &iTick);
    void ExitLevel();
    void Clean();
    void OursStepInGame();
    void AliensStepInGame(const int &iTime);
    void PrizesStepInGame(const int &iTime);
    void BulletsStepInGame();
    void BulletsExplosionStepInGame();
    void BigExplosionStepInGame();
    void CleanOursStepInGame();
    void CleanAliensStepInGame();
    void CleanPrizesStepInGame();
    void CleanBulletsStepInGame();
    void CleanBulletsExplosionStepInGame();
    void CleanBigExplosionStepInGame();
    static bool CellLessThan(const QPoint &p1, const QPoint &p2);
private:
    static int m_siCellsInRowQuantity;
    static int m_siCellsInColumnQuantity;
    int m_iSizeOfSideOfCell;
    QVector<QVector<LabyrinthCell*> > m_qvec_LabyrinthCell;
    OurPanzer * m_pOurPanzer;
    FlagPrize * m_pOurFlag;
    QList<Prize*> m_qlist_Prizes;
    QList<AlienPanzer*> m_qlist_Aliens;
    QList<AlienPanzer*> m_qlist_ExternalAliens;
    QList<Bullet*> m_qlist_Bullets;
    QList<BulletExplosion*> m_qlist_BulletExplosions;
    QList<BigExplosion*> m_qlist_BigExplosions;
    int m_iGameTick;
    int m_iTimerId;
    bool m_bGameOver;
    bool m_bFrozeAliens;
    int m_iTimeFroze;
    int m_iDeadTime;
    GameStatistic * m_pGameStatistic;
    AudioDelegate * m_pAudioDelegate;
//    QSound * m_pSound_Move;
//    QSound * m_pSound_Stop;
};
//=================================================================================================================
#endif // LABIRINTH_H
