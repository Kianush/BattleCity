#ifndef BULLET_H
#define BULLET_H
//=================================================================================================================
#include "DynamicGameThings.h"
//=================================================================================================================
class Bullet : public DynamicGameThings
{
public:
    Bullet(const int &iColumn, const int &iRow,
           const int &iXDiplace, const int &iYdiplace,
           const int &iVelosity, const DynamicGameThings::Orientation &eOrientation);
    virtual ~Bullet();
    virtual void Draw(QPainter *pPainter);
    virtual void PlaySoundAtBornMoment(){}
    virtual void PlaySoundAtDeadMoment(){}
    virtual void Move(bool &bCellChange);
    virtual void BulletHitHandler(Bullet * pBullet);
    bool IsMarkedToDelete() const;
    void MarkToDelete();
    int GetCodeOwner() const {return m_iCodeOwnersOfTheBullet;}
    void SetCodeOwner(const int &iCodeOwner) {m_iCodeOwnersOfTheBullet = iCodeOwner;}
    DynamicGameThings * GetPointerParent() {return m_pParent;}
    void SetParent(DynamicGameThings * pParent);
    DynamicGameThings::Orientation GetMoveOrientation() const;
private:
    bool m_bMarkToDelete;
    int m_iCodeOwnersOfTheBullet;
    DynamicGameThings * m_pParent;
};
//=================================================================================================================
#endif // BULLET_H
