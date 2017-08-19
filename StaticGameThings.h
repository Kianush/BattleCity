#ifndef STATICGAMETHINGS_H
#define STATICGAMETHINGS_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class DynamicGameThings;
//===============================================================================================================
class StaticGameThings : public GameThings
{
public:
    StaticGameThings(const int &iColumn, const int &iRow);
    virtual ~StaticGameThings();
};
//===============================================================================================================
#endif // STATICGAMETHINGS_H
