#ifndef KILLTHEMALLPRIZE_H
#define KILLTHEMALLPRIZE_H
//=================================================================================================================
#include "PrizesThings.h"
#include "PrizesPathes.h"
//=================================================================================================================
class Labyrinth;
//=================================================================================================================
class KillThemAllPrize : public Prize
{
public:
    KillThemAllPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth);
    virtual ~KillThemAllPrize();
    virtual void Draw(QPainter *pPainter);
    virtual bool OurPanzerHanler(OurPanzer * pOurPanzer);
    static void SetKillThemAllPrizePath();
private:
    Labyrinth * m_pLabyrinth;
    void KillThemAll();
    static KillThemAllPrizePath m_sKillThemAllPrizePath;
};
//=================================================================================================================
#endif // KILLTHEMALLPRIZE_H
