#ifndef OURPANZER_H
#define OURPANZER_H
//=================================================================================================================
#include "AlienPanzers.h"
//=================================================================================================================
class QRectF;
//=================================================================================================================
class OurPanzer : public AlienPanzer
{
public:
    OurPanzer(const int &iColumn, const int &iRow);
    virtual ~OurPanzer();
    virtual Bullet * Shoot();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void Move(bool &bCellChange);
    virtual void SetOrientation(const DynamicGameThings::Orientation &eOrientation);
    QRectF GetBoundingRect();
    bool IsShooting() const;
    void UnsetShootingSign();
    bool CanMoveIntoCurrentCell() const;
    static int GetLiveCount();
    static void SetLiveCount(const int &iLiveCount);
protected:
    virtual QString GetStringImage() const;
private:
    int GetMyCodeOfBullet() const;
    bool m_bStoping;
    bool m_bIsShooting;
    static int m_siLiveCount;
};
//=================================================================================================================
#endif // OURPANZER_H
