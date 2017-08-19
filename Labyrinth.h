#ifndef LABIRINTH_H
#define LABIRINTH_H
//=================================================================================================================
#include <QWidget>
#include <QVector>
#include <QList>
//=================================================================================================================
/// @brief decrarations
class LabyrinthCell;
class GameThings;
class AlienPanzer;
class OurPanzer;
class Prize;
class Bullet;
class FlagPrize;
class GameStatistic;
//=================================================================================================================
class Labyrinth : public QWidget
{
Q_OBJECT
public:
    Labyrinth(const int iSizeOfSideOfCell,
              QWidget * pParent = nullptr);
    virtual ~Labyrinth();
    void draw(QPainter *pPainter);
    void KillAllAliens();
    static void SetDimension(const int &iQuantityRows, const int &iQuantityColumns);
    static void SetInternalStaticVariables(GameStatistic *pGameStatistic,
                                           const int &iOwnerCodeOfBulletsOfAliens);
    void DoGameOver();
signals:
    void sigGameOver();
protected:
    virtual void timerEvent(QTimerEvent * pTimerEvent);
    virtual void paintEvent(QPaintEvent * pPaintEvent);
    virtual void keyPressEvent(QKeyEvent * pKeyEvent);
    virtual void keyReleaseEvent(QKeyEvent * pKeyEvent);
private:
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
    void ExitLevel();
    void Clean();
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
    int m_iGameTick;
    int m_iTimerId;
    bool m_bGameOver;
    GameStatistic * m_pGameStatistic;
};
//=================================================================================================================
#endif // LABIRINTH_H
