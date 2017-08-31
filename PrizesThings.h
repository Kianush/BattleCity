#ifndef PRIZESTHINGS_H
#define PRIZESTHINGS_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class OurPanzer;
//===============================================================================================================
class Prize : public GameThings
{
public:
    Prize(const int &iColumn, const int &iRow);
    virtual ~Prize();
    void SetPrizeCost(const int &iPrizeCost);
    int GetPrizeCost() const;
    bool IsMarkedToDelete() const;
    void DecrementShowPrizeCostTime();
    void DecrementLiveTime();
    void MarkToDelete();
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool OurPanzerHanler(OurPanzer * pOurPanzer);
    virtual QString GetStringImage() const;
    bool IsEffect() const;
private:
    int m_iPrizeCost;
    bool m_bIsMarkedToDelete;
    bool m_bIsEffect;
    int m_iShowPrizeCostTime;
    int m_iLiveTime;
};
//===============================================================================================================
#endif // PRIZESTHINGS_H
