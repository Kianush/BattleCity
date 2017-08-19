#ifndef GAMETHINGS_H
#define GAMETHINGS_H
//=================================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
class GameStatistic;
//=================================================================================================================
class GameThings
{
public:
    GameThings(const int &iColumn, const int &iRow);
    virtual ~GameThings();
    virtual void Draw(QPainter *pPainter) = 0;
    virtual void BulletHitHandler(Bullet * pBullet) = 0;
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    virtual void PlaySoundAtBornMoment() = 0;
    virtual void PlaySoundAtDeadMoment() = 0;
    int GetColumn() const {return m_iColumn;}
    void SetColumn(const int &iColumn) {m_iColumn = iColumn;}
    int GetRow() const {return m_iRow;}
    void SetRow(const int &iRow) {m_iRow = iRow;}
    int GetXdiplace() const {return m_iXdiplace;}
    void SetXdiplace(const int &iXdiplace) {m_iXdiplace = iXdiplace;}
    int GetYdiplace() const {return m_iYdiplace;}
    void SetYdiplace(const int &iYdiplace) {m_iYdiplace = iYdiplace;}
    static void SetCellSizeOfSide(const int &iCellSizeOfSide);
    static void SetPointerGameStatistic(GameStatistic * psGameStatistic);
    static GameStatistic * GetPointerGameStatistic();
protected:
    int m_iColumn;
    int m_iRow;
    int m_iXdiplace;
    int m_iYdiplace;
    static int GetCellSide();
    static GameStatistic * m_psGameStatistic;
private:
    static int m_siCellSizeOfSide;
};
//=================================================================================================================
#endif // GAMETHINGS_H
