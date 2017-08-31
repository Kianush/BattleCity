#ifndef ALIENPANZERS_H
#define ALIENPANZERS_H
//================================================================================================================
#include "DynamicGameThings.h"
//================================================================================================================
class Bullet;
class QString;
//================================================================================================================
class AlienPanzer : public DynamicGameThings
{
public:
    AlienPanzer(const int &iColumn, const int &iRow);
    virtual ~AlienPanzer();
    virtual Bullet *Shoot();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void Move(bool &bCellChange);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    virtual void SetOrientation(const DynamicGameThings::Orientation &eOrientation);

    void DummyRotate();
    void MarkToDelete();
    bool IsMarkedToDelete() const;
    bool IsDead() const;
    void DecrementShowCostTime();
    void DecreaseBornTime(const int &iTick);
    void SetBorning();
    bool IsBorning() const;
    void SetTypicalVelosity();
    int GetWidth() const;
    int GetHeight() const;
    void SetFrozen(const bool &bFrozen);
    bool IsFrozen() const;
    static void SetCodeOwnerOfBullets(const int &iCodeOwner);
    static void SetQuantitySimpleAliens(const int &iQuantitySimpleAliens);
    static void DecrementQuantityAliens();
    static int GetQuantitySimpleAliens();
    static void ResetAliensInGame(const int &iQuantityAliensInGame);
    static void SetDimensionsOfMainImage(const int &iWidth, const int iHeight);
protected:
    bool m_bIsMarkedToDelete;
    void SetCost(const int &iCost);
    int GetCost() const;
    virtual void SetStatistic();
    virtual int GetTypicalVelosity() const;
    virtual QString GetStringImage() const;
    static int m_siNumberOfTheAlien;
    static int m_siCodeOwnerOfBullet;
private:
    int m_iShowCostTime;
    int m_iShowBorningTime;
    bool m_bIsDead;
    bool m_bIsBorning;
    bool m_bIsFrozen;
    int m_iCost;

    static int m_siWidthOfMainImage;
    static int m_siHeightOfMainImage;
    static int m_siQuantitySimpleAliensInGame;
};
//================================================================================================================
#endif // ALIENPANZERS_H
