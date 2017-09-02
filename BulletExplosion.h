#ifndef BULLETEXPLOSION_H
#define BULLETEXPLOSION_H
//=================================================================================================================
#include "GameThings.h"
//=================================================================================================================
class BulletExplosion : public GameThings
{
public:
    BulletExplosion(const int &iColumn, const int &iRow,
                    const int &iXDiplace, const int &iYdiplace);
    virtual ~BulletExplosion();
    virtual QString GetStringImage() const;
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    void DecrementTick();
    int GetTick() const;
private:
    int m_iTick;
    static int m_siNumberOfBulletExplosion;
};
//=================================================================================================================
#endif // BULLETEXPLOSION_H
