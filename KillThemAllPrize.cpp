#include "KillThemAllPrize.h"
#include "Labyrinth.h"
#include "GameStatistic.h"
//=================================================================================================================
#include <QPainter>
//=================================================================================================================
KillThemAllPrizePath KillThemAllPrize::m_sKillThemAllPrizePath;
//=================================================================================================================
void KillThemAllPrize::SetKillThemAllPrizePath()
{
    QMatrix matrix;
    matrix.rotate(180);
    m_sKillThemAllPrizePath.m_KillThemAllPrizePainterPath =
            matrix.map(m_sKillThemAllPrizePath.m_KillThemAllPrizePainterPath);
}
//=================================================================================================================
KillThemAllPrize::KillThemAllPrize(const int &iColumn, const int &iRow, Labyrinth *pLabyrinth) : Prize(iColumn, iRow)
{
    m_pLabyrinth = pLabyrinth;
}
//=================================================================================================================
KillThemAllPrize::~KillThemAllPrize()
{

}
//=================================================================================================================
void KillThemAllPrize::Draw(QPainter *pPainter)
{
    static int iBlinkCounter = 0;
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pPainter->setPen(pen);
    pPainter->setBrush(Qt::NoBrush);
    if (IsEffect()) {
        pPainter->setBrush(Qt::NoBrush);

        pPainter->drawText(m_iColumn*GetCellSide() + m_iXdiplace+2,
                           m_iRow*GetCellSide() + m_iYdiplace+25, "+" + QString::number(GetPrizeCost()));
    }
    else {
        QPoint qpointTranslatedPosition = QPoint(m_iColumn*GetCellSide() + m_iXdiplace + GetCellSide()/2,
                                                 m_iRow*GetCellSide() + m_iYdiplace + GetCellSide()/2);


        if ((iBlinkCounter/10) % 2 == 0) {
            pPainter->drawPath(m_sKillThemAllPrizePath.m_KillThemAllPrizePainterPath.translated(qpointTranslatedPosition));
        }
    }
    iBlinkCounter++;
}
//=================================================================================================================
void KillThemAllPrize::KillThemAll()
{
    m_pLabyrinth->KillAllAliens();
}
//=================================================================================================================
bool KillThemAllPrize::OurPanzerHanler(OurPanzer * pOurPanzer)
{
    bool bToReturn = Prize::OurPanzerHanler(pOurPanzer);
    if (bToReturn) {
        KillThemAll();
        m_psGameStatistic->AddScope(GetPrizeCost());
    }
    return bToReturn;
}
//=================================================================================================================
