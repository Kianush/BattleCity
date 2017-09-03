#include "FreeSpace.h"
//==================================================================================================================
#include "Bullet.h"
//===============================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//===============================================================================================================
FreeSpace::FreeSpace(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    QString qmlObjectName = "c" + QString::number(iColumn) + "r" + QString::number(iRow);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
//    if (nullptr != m_pQmlImage) {
//        m_pQmlImage->setProperty("texture", QString("Images/free_space.png"));
//    }
}
//===============================================================================================================
QString FreeSpace::GetStringImage() const
{
    return QString("Images/free_space.png");
}
//===============================================================================================================
FreeSpace::~FreeSpace()
{
//    if (nullptr != m_pQmlImage) {
//        m_pQmlImage->setProperty("x", -GetCellSide());
//        m_pQmlImage->setProperty("y", -GetCellSide());
//        m_pQmlImage->setProperty("active", false);
//    }
}
//===============================================================================================================
//void FreeSpace::Draw()
//{
////    Q_UNUSED(pPainter)
////    QPen pen;
////    pen.setWidth(0);
////    QBrush Brush(QColor(200, 200, 200));
////    pPainter->setPen(Qt::NoPen);
////    pPainter->setBrush(Brush);
////    pPainter->drawRect(m_iColumn*GetCellSide(), m_iRow*GetCellSide(), GetCellSide(), GetCellSide());
//    if (nullptr != m_pQmlImage) {
//        m_pQmlImage->setProperty("x", m_iColumn*GetCellSide() + m_iXdiplace);
//        m_pQmlImage->setProperty("y", m_iRow*GetCellSide() + m_iYdiplace);
//        m_pQmlImage->setProperty("active", true);
//    }
//}
//===============================================================================================================
void FreeSpace::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//===============================================================================================================
bool FreeSpace::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return true;
}
//===============================================================================================================
