#ifndef BIGEXPLOSION_H
#define BIGEXPLOSION_H
//=================================================================================================================
#include "BulletExplosion.h"
//=================================================================================================================
class BigExplosion : public GameThings
{
public:
    BigExplosion(const int &iColumn, const int &iRow);
    virtual ~BigExplosion();
    virtual QString GetStringImage() const;
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    void DecrementTick();
    int GetTick() const;
private:
    int m_iTick;
    static int m_siNumberOfBigExplosion;
};
//=================================================================================================================
#endif // BIGEXPLOSION_H
