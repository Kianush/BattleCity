#include "PanzersPathes.h"
//================================================================================================================
AlienPath::AlienPath()
{
    m_AlienPanzerPainterPath.moveTo(-10, 15);
    m_AlienPanzerPainterPath.lineTo(-6, 15);
    m_AlienPanzerPainterPath.lineTo(-6, -15);
    m_AlienPanzerPainterPath.lineTo(-10, -15);
    m_AlienPanzerPainterPath.lineTo(-10, 15);
    m_AlienPanzerPainterPath.moveTo(6, 15);
    m_AlienPanzerPainterPath.lineTo(10, 15);
    m_AlienPanzerPainterPath.lineTo(10, -15);
    m_AlienPanzerPainterPath.lineTo(6, -15);
    m_AlienPanzerPainterPath.lineTo(6, 15);
    m_AlienPanzerPainterPath.moveTo(-6, 10);
    m_AlienPanzerPainterPath.lineTo(-2, 10);
    m_AlienPanzerPainterPath.lineTo(-2, 5);
    m_AlienPanzerPainterPath.lineTo(-4, 3);
    m_AlienPanzerPainterPath.lineTo(-5, 0);
    m_AlienPanzerPainterPath.lineTo(-4, -3);
    m_AlienPanzerPainterPath.lineTo(-3, -4);
    m_AlienPanzerPainterPath.lineTo(0, -5);
    m_AlienPanzerPainterPath.lineTo(3, -4);
    m_AlienPanzerPainterPath.lineTo(4, -3);
    m_AlienPanzerPainterPath.lineTo(5, 0);
    m_AlienPanzerPainterPath.lineTo(4, 3);
    m_AlienPanzerPainterPath.lineTo(3, 4);
    m_AlienPanzerPainterPath.lineTo(2, 5);
    m_AlienPanzerPainterPath.lineTo(2, 10);
    m_AlienPanzerPainterPath.lineTo(6, 10);
    m_AlienPanzerPainterPath.lineTo(6, -10);
    m_AlienPanzerPainterPath.lineTo(-6, -10);
    m_AlienPanzerPainterPath.lineTo(-6, 10);

    m_AlienPanzerPainterPath.moveTo(-2, 10);
    m_AlienPanzerPainterPath.lineTo(-2, 13);
    m_AlienPanzerPainterPath.lineTo(-3, 13);
    m_AlienPanzerPainterPath.lineTo(-3, 15);
    m_AlienPanzerPainterPath.lineTo(3, 15);
    m_AlienPanzerPainterPath.lineTo(3, 13);
    m_AlienPanzerPainterPath.lineTo(2, 13);
    m_AlienPanzerPainterPath.lineTo(2, 10);
}
//================================================================================================================
AlienBornPath::AlienBornPath()
{
    m_PulseFirstPainterPath.moveTo(0, 15);
    m_PulseFirstPainterPath.lineTo(1, 10);
    m_PulseFirstPainterPath.lineTo(2, 5);
    m_PulseFirstPainterPath.lineTo(3, 3);
    m_PulseFirstPainterPath.lineTo(5, 2);
    m_PulseFirstPainterPath.lineTo(10, 1);
    m_PulseFirstPainterPath.lineTo(15, 0);
    m_PulseFirstPainterPath.lineTo(10, -1);
    m_PulseFirstPainterPath.lineTo(5, -2);
    m_PulseFirstPainterPath.lineTo(3, -3);
    m_PulseFirstPainterPath.lineTo(2, -5);
    m_PulseFirstPainterPath.lineTo(1, -10);
    m_PulseFirstPainterPath.lineTo(0, -15);
    m_PulseFirstPainterPath.lineTo(-1, -10);
    m_PulseFirstPainterPath.lineTo(-2, -5);
    m_PulseFirstPainterPath.lineTo(-3, -3);
    m_PulseFirstPainterPath.lineTo(-5, -2);
    m_PulseFirstPainterPath.lineTo(-10, -1);
    m_PulseFirstPainterPath.lineTo(-15, 0);
    m_PulseFirstPainterPath.lineTo(-10, 1);
    m_PulseFirstPainterPath.lineTo(-5, 2);
    m_PulseFirstPainterPath.lineTo(-3, 3);
    m_PulseFirstPainterPath.lineTo(-2, 5);
    m_PulseFirstPainterPath.lineTo(-1, 10);
     m_PulseFirstPainterPath.lineTo(0, 15);

    m_PulseSecondPainterPath.moveTo(0, 10);
    m_PulseSecondPainterPath.lineTo(1, 3);
    m_PulseSecondPainterPath.lineTo(2, 2);
    m_PulseSecondPainterPath.lineTo(3, 1);
    m_PulseSecondPainterPath.lineTo(10, 0);
    m_PulseSecondPainterPath.lineTo(3, -1);
    m_PulseSecondPainterPath.lineTo(2, -2);
    m_PulseSecondPainterPath.lineTo(1, -3);
    m_PulseSecondPainterPath.lineTo(0, -10);
    m_PulseSecondPainterPath.lineTo(-1, -3);
    m_PulseSecondPainterPath.lineTo(-2, -2);
    m_PulseSecondPainterPath.lineTo(-3, -1);
    m_PulseSecondPainterPath.lineTo(-10, 0);
    m_PulseSecondPainterPath.lineTo(-3, 1);
    m_PulseSecondPainterPath.lineTo(-2, 2);
    m_PulseSecondPainterPath.lineTo(-1, 3);
    m_PulseSecondPainterPath.lineTo(0, 10);
}
//================================================================================================================
