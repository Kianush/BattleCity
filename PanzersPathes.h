#ifndef PANZERSPATHES_H
#define PANZERSPATHES_H
//================================================================================================================
#include <QPainterPath>
//================================================================================================================
class AlienPath
{
public:
    AlienPath();
    ~AlienPath(){}
    QPainterPath m_AlienPanzerPainterPath;
};
//================================================================================================================
class AlienBornPath
{
public:
    AlienBornPath();
    ~AlienBornPath(){}
    QPainterPath m_PulseFirstPainterPath;
    QPainterPath m_PulseSecondPainterPath;
};
//================================================================================================================
#endif // PANZERSPATHES_H
