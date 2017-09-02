#ifndef BULLET_H
#define BULLET_H
//=================================================================================================================
#include "DynamicGameThings.h"
//=================================================================================================================
class QObject;
class BulletExplosion;
//=================================================================================================================
class Bullet : public DynamicGameThings
{
public:
    Bullet(const int &iColumn, const int &iRow,
           const int &iXDiplace, const int &iYdiplace,
           const int &iVelosity, const DynamicGameThings::Orientation &eOrientation);
    virtual ~Bullet();
//    virtual void Draw();
    virtual void Move(bool &bCellChange);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual QString GetStringImage() const;
    bool IsMarkedToDelete() const;
    void MarkToDelete();
    int GetCodeOwner() const {return m_iCodeOwnersOfTheBullet;}
    void SetCodeOwner(const int &iCodeOwner) {m_iCodeOwnersOfTheBullet = iCodeOwner;}
    DynamicGameThings * GetPointerParent() {return m_pParent;}
    void SetParent(DynamicGameThings * pParent);
    DynamicGameThings::Orientation GetMoveOrientation() const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    BulletExplosion * GetExplosion() const;
    static void SetDimensionsOfBullet(const int &iWidth, const int &iHeight);
    void SetCentrExplosion(const int &iExplosionX, const int &iExplosionY);
protected:
    virtual int GetX() const;
    virtual int GetY() const;
private:
    bool m_bMarkToDelete;
    int m_iCodeOwnersOfTheBullet;
    int m_iExplosionX;
    int m_iExplosionY;
    DynamicGameThings * m_pParent;
    static int m_siNumberOfBullet;
    static int m_siBulletWidth;
    static int m_siBulletHeight;

//    QObject * m_pQmlImage;
};
//=================================================================================================================
#endif // BULLET_H
