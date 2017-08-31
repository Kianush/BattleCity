#include "ImplicitInternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//===============================================================================================================
ImplicitInternalWall::ImplicitInternalWall(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    SetLiveHits(2);
    QString qmlObjectName = "c" + QString::number(iColumn) + "r" + QString::number(iRow);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
    if (nullptr != m_pQmlImage) {
        m_pQmlImage->setProperty("texture", QString("Images/internal_wall.png"));
    }
}
//===============================================================================================================
ImplicitInternalWall::~ImplicitInternalWall()
{
//    if (nullptr != m_pQmlImage) {
//        m_pQmlImage->setProperty("x", -GetCellSide());
//        m_pQmlImage->setProperty("y", -GetCellSide());
//        m_pQmlImage->setProperty("active", false);
//    }
}
//===============================================================================================================
QString ImplicitInternalWall::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[3];
    qstrArrayImages[2] = "Images/internal_wall.png";
    qstrArrayImages[1] = "Images/internal_wall_1.png";
    qstrArrayImages[0] = "Images/internal_wall_2.png";
    if (nullptr != m_pQmlImage) {
        switch (GetLiveHits()) {
            case 2:
                qstrToReturn = qstrArrayImages[2];
            break;
            case 1:
                qstrToReturn = qstrArrayImages[1];
            break;
            case 0:
                qstrToReturn = qstrArrayImages[0];
            break;
            default:
            break;
        }
    }
    return qstrToReturn;
}
//===============================================================================================================
//void ImplicitInternalWall::Draw()
//{
////    QBrush theBrush;
////    switch (m_iLiveHits) {
////    case 2:
////        theBrush = (QColor(200, 200, 200), Qt::SolidPattern);
////        break;
////    case 1:
////        theBrush = (QColor(200, 200, 200), Qt::Dense1Pattern);
////        break;
////    case 0:
////        theBrush = (QColor(200, 200, 200), Qt::Dense2Pattern);
////        break;
////    default:
////        break;
////    }
////    pPainter->setBrush(theBrush);
////    pPainter->drawRect(m_iColumn*40 + m_iXdiplace, m_iRow*40 + m_iYdiplace,40,40);

//    static QString qstrArrayImages[3];
//    qstrArrayImages[2] = "Images/internal_wall.png";
//    qstrArrayImages[1] = "Images/internal_wall_1.png";
//    qstrArrayImages[0] = "Images/internal_wall_2.png";
//    if (nullptr != m_pQmlImage) {
//        switch (GetLiveHits()) {
//            case 2:
//                if (m_pQmlImage->property("texture").toString() != qstrArrayImages[2]) {
//                    m_pQmlImage->setProperty("texture", qstrArrayImages[2]);
//                }
//            break;
//            case 1:
//                if (m_pQmlImage->property("texture").toString() != qstrArrayImages[1]) {
//                    m_pQmlImage->setProperty("texture", qstrArrayImages[1]);
//                }
//            break;
//            case 0:
//                if (m_pQmlImage->property("texture").toString() != qstrArrayImages[0]) {
//                    m_pQmlImage->setProperty("texture", qstrArrayImages[0]);
//                }
//            break;
//            default:
//            break;
//        }
//        m_pQmlImage->setProperty("x", m_iColumn*GetCellSide() + m_iXdiplace);
//        m_pQmlImage->setProperty("y", m_iRow*GetCellSide() + m_iYdiplace);
//        m_pQmlImage->setProperty("active", true);
//    }
//}
//===============================================================================================================
void ImplicitInternalWall::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
    DecrementLiveHits();
}
//===============================================================================================================
bool ImplicitInternalWall::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return false;
}
//===============================================================================================================
