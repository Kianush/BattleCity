#ifndef ALIENPANZERS_H
#define ALIENPANZERS_H
//================================================================================================================
#include "DynamicGameThings.h"
#include "PanzersPathes.h"
//================================================================================================================
class Bullet;
//================================================================================================================
class AlienPanzer : public DynamicGameThings
{
public:
    AlienPanzer(const int &iColumn, const int &iRow);
    virtual ~AlienPanzer();
    virtual void Draw(QPainter *pPainter);
    virtual void PlaySoundAtBornMoment(){}
    virtual void PlaySoundAtDeadMoment(){}
    virtual Bullet *Shoot();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void Move(bool &bCellChange);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    virtual void SetOrientation(const DynamicGameThings::Orientation &eOrientation);
    void DummyRotate();
    static void SetRotatedSimpleAlienPathes();
    static void SetCodeOwnerOfBullets(const int &iCodeOwner);
    static void SetQuantitySimpleAliens(const int &iQuantitySimpleAliens);
    static int GetQuantitySimpleAliens();
    bool IsMarkedToDelete() const;
    void MarkToDelete();
    bool IsDead() const;
    void DecrementShowCostTime();
    void DecreaseBornTime(const int &iTick);
    void SetBorning();
    bool IsBorning() const;
    void SetTypicalVelosity();
protected:
    static AlienPath m_sAlienPainterPathLeft;
    static AlienPath m_sAlienPainterPathRight;
    static AlienPath m_sAlienPainterPathUp;
    static AlienPath m_sAlienPainterPathDown;
    static AlienBornPath m_sAlienBornPath;
    static int m_siCodeOwnerOfBullet;
    bool m_bIsMarkedToDelete;
    int m_iLiveHits;
    void SetCost(const int &iCost);
    int GetCost() const;
    virtual void SetStatistic();
    virtual int GetTypicalVelosity() const;
private:
    int m_iShowCostTime;
    int m_iShowBorningTime;
    bool m_bIsDead;
    bool m_bIsBorning;
    int m_iCost;
    static int m_siQuantitySimpleAliensInGame;
};
//================================================================================================================
#endif // ALIENPANZERS_H
