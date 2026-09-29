#pragma once

#include <random>
#include <vector>
#include "Card.h"

class Deck
{
private:
    std::vector<Card> cards_;
    std::mt19937 randomEngine_;

public:
    Deck();

    void Reset();
    void Shuffle();

    Card DrawCard();

    int GetRemainingCardCount() const;
    bool IsEmpty() const;
};