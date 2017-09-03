#ifndef KILLTHEMALLPRIZE_H
#define KILLTHEMALLPRIZE_H
//=================================================================================================================
#include "PrizesThings.h"
//=================================================================================================================
class Labyrinth;
//=================================================================================================================
class KillThemAllPrize : public Prize
{
public:
    KillThemAllPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth);
    virtual ~KillThemAllPrize();
    virtual QString GetStringImage() const;
    virtual bool OurPanzerHanler(OurPanzer * pOurPanzer);
private:
    Labyrinth * m_pLabyrinth;
    void KillThemAll();
};
//=================================================================================================================
#endif // KILLTHEMALLPRIZE_H
