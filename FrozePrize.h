#ifndef FROZEPRIZE_H
#define FROZEPRIZE_H
//=================================================================================================================
#include "PrizesThings.h"
//=================================================================================================================
class Labyrinth;
//=================================================================================================================
class FrozePrize : public Prize
{
public:
    FrozePrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth);
    virtual ~FrozePrize();
    virtual QString GetStringImage() const;
    virtual bool OurPanzerHanler(OurPanzer * pOurPanzer);
private:
     Labyrinth * m_pLabyrinth;
     void Froze();
};
//=================================================================================================================
#endif // FROZEPRIZE_H
