#include "Card.h"
#include "GameConfig.h"

Card::Card(): value_(GameConfig::MIN_CARD_VALUE)
{
}

Card::Card(int value): value_(value)
{
}

int Card::GetValue() const
{
    return value_;
}