#include "FrozePrize.h"
#include "Labyrinth.h"
#include "GameStatistic.h"
//=================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//=================================================================================================================
FrozePrize::FrozePrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth) : Prize(iColumn, iRow)
{
    m_pLabyrinth = pLabyrinth;
    QString qmlObjectName = "prize";
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//=================================================================================================================
FrozePrize::~FrozePrize()
{

}
//=================================================================================================================
QString FrozePrize::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[3];
    qstrArrayImages[0] = "Images/froze.png";
    qstrArrayImages[1] = "Images/kill_them_all_empty.png";
    qstrArrayImages[2] = "Images/plus_500.png";

    static int iBlinkCounter = 0;
    if (IsEffect()) {
        qstrToReturn = qstrArrayImages[2];
    }
    else {
        if ((iBlinkCounter/10) % 2 == 0) {
            qstrToReturn = qstrArrayImages[1];
        }
        else {
            qstrToReturn = qstrArrayImages[0];
        }
    }
    iBlinkCounter++;
    return qstrToReturn;
}
//=================================================================================================================
bool FrozePrize::OurPanzerHanler(OurPanzer * pOurPanzer)
{
    bool bToReturn = Prize::OurPanzerHanler(pOurPanzer);
    if (bToReturn) {
        Froze();
        m_psGameStatistic->AddScope(GetPrizeCost());
    }
    return bToReturn;
}
//=================================================================================================================
void FrozePrize::Froze()
{
    m_pLabyrinth->FrozeAliens();
}
//=================================================================================================================
