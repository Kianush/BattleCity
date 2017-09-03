#include "SpeedAlienPanzer.h"
#include "GameStatistic.h"
//=============================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//=============================================================================================================
SpeedAlienPanzer::SpeedAlienPanzer(const int &iColumn, const int &iRow) : AlienPanzer(iColumn, iRow)
{
    SetVelosity(10);
    SetCost(200);
}
//=============================================================================================================
SpeedAlienPanzer::~SpeedAlienPanzer()
{

}
//=============================================================================================================
QString SpeedAlienPanzer::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[7];
    qstrArrayImages[0] = "Images/alien_panzer_nord.png";
    qstrArrayImages[1] = "Images/alien_panzer_east.png";
    qstrArrayImages[2] = "Images/alien_panzer_south.png";
    qstrArrayImages[3] = "Images/alien_panzer_west.png";
    qstrArrayImages[4] = "Images/pulse_1.png";
    qstrArrayImages[5] = "Images/pulse_2.png";
    qstrArrayImages[6] = "Images/plus_200.png";
    if (!IsDead() && !IsBorning()) {
        switch (m_eOrientation) {
            case Up:
                qstrToReturn = qstrArrayImages[0];
            break;
            case Right:
                qstrToReturn = qstrArrayImages[1];
            break;
            case Down:
                qstrToReturn = qstrArrayImages[2];
            break;
            case Left:
                qstrToReturn = qstrArrayImages[3];
            break;
            default:
            break;
        }
    }
    else if (IsBorning()) {
        static int iPulseCounter = 0;
        if ((iPulseCounter/7) % 2 == 0) {
            qstrToReturn = qstrArrayImages[4];
        }
        else {
            qstrToReturn = qstrArrayImages[5];
        }
        iPulseCounter++;
    }
    else if (IsDead()) {
        qstrToReturn = qstrArrayImages[6];
    }
    else {}
    return qstrToReturn;
}
//=============================================================================================================
void SpeedAlienPanzer::SetStatistic()
{
    m_psGameStatistic->AddScope(GetCost());
    m_psGameStatistic->IncrementSpeedAliensKilled();
}
//=============================================================================================================
int SpeedAlienPanzer::GetTypicalVelosity() const
{
    return 2*(AlienPanzer::GetTypicalVelosity());
}
//=============================================================================================================
