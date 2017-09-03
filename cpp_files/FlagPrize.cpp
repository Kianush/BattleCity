#include "FlagPrize.h"
#include "Labyrinth.h"
#include "Bullet.h"
#include "AudioDelegate.h"
//================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//================================================================================================================
FlagPrize::FlagPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth) : Prize(iColumn, iRow)
{
    m_pLabyrinth = pLabyrinth;
    QString qmlObjectName = "our_flag";
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//================================================================================================================
FlagPrize::~FlagPrize()
{
}
//================================================================================================================
QString FlagPrize::GetStringImage() const
{
    return QString("Images/flag_prize.png");
}
//================================================================================================================
bool FlagPrize::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return false;
}
//================================================================================================================
void FlagPrize::BulletHitHandler(Bullet * pBullet)
{
    SetExplosion();
    m_psAudioDelegate->PlayExplosion();
    pBullet->MarkToDelete();
    MarkToDelete();
    GameOver();
}
//================================================================================================================
void FlagPrize::GameOver()
{
    m_pLabyrinth->DoGameOver();
}
//================================================================================================================
